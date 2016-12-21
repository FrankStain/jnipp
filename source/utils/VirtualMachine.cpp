// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#include <jnipp/jnipp.h>
#include <jnipp/android/ThreadHandle.h>
#include <jnipp/android/ClassLoaderHandle.h>
#include <pthread.h>


namespace Jni
{
	VirtualMachine& VirtualMachine::GetInstance()
	{
		static VirtualMachine vm;
		return vm;
	};

	const bool VirtualMachine::Initialize( JavaVM* jvm )
	{
		JNI_EXPECTS( jvm != nullptr );

		auto& vm = GetInstance();
		JNI_RETURN_IF_E(
			jvm->GetEnv( reinterpret_cast<void**>( &vm.m_main_env ), VirtualMachine::JNI_VERSION ) != JNI_OK,
			false,
			"Failed to get main JNI Environment."
		);

		vm.m_jvm			= jvm;
		vm.m_main_thread_id	= pthread_self();

		JNI_ENSURES( pthread_key_create( &reinterpret_cast<pthread_key_t&>( vm.m_detach_key ), VirtualMachine::DetachLocalEnv ) == 0 )
		JNI_ENSURES( vm.m_jvm != nullptr );
		JNI_ENSURES( vm.m_main_env != nullptr );

		JNI_RETURN_IF_E( !vm.CaptureClassLoader(), false, "Failed to capture the class loader." );
		JNI_RETURN_IF_E( !vm.AcquireClassInterface(), false, "Failed to acquire the interface of `java.lang.Class` class." );
		return true;
	};

	void VirtualMachine::Finalize()
	{
		auto& vm = GetInstance();

		pthread_key_delete( vm.m_detach_key );

		vm.m_jvm			= nullptr;
		vm.m_main_env		= nullptr;
		vm.m_main_thread_id	= 0;
	};

	const bool VirtualMachine::CaptureClassLoader()
	{
		Class loader_class{ "java/lang/ClassLoader" };
		JNI_RETURN_IF_E( !loader_class, false, "Failed to locate `java.lang.ClassLoader` class." );

		m_load_class_func = { loader_class, "loadClass" };
		JNI_RETURN_IF_E( !m_load_class_func, false, "Failed to locate `Class ClassLoader::findClass( String )` function." );

		Class thread_class{ "java/lang/Thread" };
		JNI_RETURN_IF_E( !thread_class, false, "Failed to locate `java.lang.Thread` class." );

		StaticFunctionHandle<ThreadHandle> current_thread_func{ thread_class, "currentThread" };
		JNI_RETURN_IF_E( !current_thread_func, false, "Failed to locate `Thread Thread::currentThread()` function." );

		ThreadHandle current_thread{ current_thread_func.Call() };
		JNI_RETURN_IF_E( !current_thread, false, "Failed to get object of current thread." );

		MemberFunction<ClassLoaderHandle> get_class_loader_func{ thread_class, "getContextClassLoader" };
		JNI_RETURN_IF_E( !get_class_loader_func, false, "Failed to locate `ClassLoader Thread::getContextClassLoader()` function." );

		m_class_loader = get_class_loader_func.Call( current_thread );
		JNI_RETURN_IF_E( !m_class_loader, false, "Failed to get class loader object." );

		return true;
	};

	const bool VirtualMachine::AcquireClassInterface()
	{
		const Class class_handle{ "java/lang/Class" };
		JNI_RETURN_IF_E( !class_handle, false, "Failed to locate `java.lang.Class` class." );

		m_get_super_class_func = { class_handle, "getSuperclass" };
		JNI_RETURN_IF_E( !m_get_super_class_func, false, "Failed to locate `Class Class::getSuperclass()` function." );

		m_get_canonical_name = { class_handle, "getCanonicalName" };
		JNI_RETURN_IF_E( !m_get_canonical_name, false, "Failed to locate `String Class::getCanonicalName()` function." );

		m_get_name = { class_handle, "getName" };
		JNI_RETURN_IF_E( !m_get_name, false, "Failed to locate `String Class::getName()` function." );

		m_get_simple_name = { class_handle, "getSimpleName" };
		JNI_RETURN_IF_E( !m_get_simple_name, false, "Failed to locate `String Class::getSimpleName()` function." );

		return true;
	};

	const bool VirtualMachine::RegisterClassNatives( const NativeBindingTable& bindings )
	{
		JNI_RETURN_IF_E( !IsValid(), nullptr, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env	= GetLocalEnvironment();
		auto java_class	= GetInstance().GetClassReference( bindings.class_name );
		JNI_RETURN_IF_E( !java_class, false, "Class `%s` was not found.", bindings.class_name );

		std::vector<JNINativeMethod> jni_natives;
		jni_natives.reserve( bindings.natives.size() );
		std::transform(
			bindings.natives.begin(), bindings.natives.end(), std::back_inserter( jni_natives ),
			[]( const NativeFunction& stored_function ) -> JNINativeMethod
			{
				return stored_function.GetJniNativeMethod();
			}
		);

		JNI_RETURN_IF_E(
			local_env->RegisterNatives( java_class.get(), jni_natives.data(), static_cast<int32_t>( jni_natives.size() ) ) != JNI_OK,
			false,
			"Failed to register natives for class `%s`.", bindings.class_name
		);

		return true;
	};

	const bool VirtualMachine::RegisterClassNatives( std::initializer_list<NativeBindingTable> bindings )
	{
		return std::all_of(
			bindings.begin(), bindings.end(),
			static_cast<const bool (*)( const NativeBindingTable& )>( VirtualMachine::RegisterClassNatives )
		);
	};

	JNIEnv* VirtualMachine::GetLocalEnvironment()
	{
		JNI_RETURN_IF_E( !IsValid(), nullptr, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto& vm = GetInstance();
		JNI_RETURN_IF_V( pthread_self() == vm.m_main_thread_id, vm.m_main_env, "Accessing JniEnv from main thread." );

		JNIEnv* local_env = nullptr;
		JNI_RETURN_IF_V( vm.m_jvm->GetEnv( reinterpret_cast<void**>( &local_env ), VirtualMachine::JNI_VERSION ) == JNI_OK, local_env, "Accessing already attached JniEnv." );

		// Try to attach JVM to this thread.
		JNI_RETURN_IF_E( vm.m_jvm->AttachCurrentThread( &local_env, nullptr ) != JNI_OK, nullptr, "Failed to attach Java VM to current thread." );
		JNI_RETURN_IF_D( pthread_getspecific( vm.m_detach_key ) != nullptr, local_env, "Looks like local JniEnv was reattached to thread." );

		JNI_RETURN_IF_E( pthread_setspecific( vm.m_detach_key, local_env ) != 0, local_env, "Failed to set thread-local detach routine for JniEnv." );
		return local_env;
	};

	void VirtualMachine::DeleteSharedClass( jclass value )
	{
		JNI_RETURN_IF_E( !IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		if( value != nullptr )
		{
			GetLocalEnvironment()->DeleteGlobalRef( value );
		};
	};

	void VirtualMachine::DetachLocalEnv( void* local_env )
	{
		JNI_EXPECTS( IsValid() );
		GetInstance().m_jvm->DetachCurrentThread();
	};

	std::shared_ptr<_jclass> VirtualMachine::GetClassReference( jobject local_object_ref )
	{
		JNI_RETURN_IF_E( !IsValid(), {}, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		JNI_RETURN_IF_V( local_object_ref == nullptr, {}, "Attempt to get Java class via null object." );

		auto local_env		= GetLocalEnvironment();
		auto local_class	= local_env->GetObjectClass( local_object_ref );
		JNI_RETURN_IF_W( local_class == nullptr, {}, "Unable to get Java class for object." );

		// The value returned is `std::shared_ptr` with custom deleter.
		return { reinterpret_cast<jclass>( local_env->NewGlobalRef( local_class ) ), VirtualMachine::DeleteSharedClass };
	};

	std::shared_ptr<_jclass> VirtualMachine::GetClassReference( jclass local_class_ref )
	{
		JNI_RETURN_IF_E( !IsValid(), {}, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		JNI_RETURN_IF_V( local_class_ref == nullptr, {}, "Attempt to get Java class via null class." );

		auto local_env = GetLocalEnvironment();

		// The value returned is `std::shared_ptr` with custom deleter.
		return { reinterpret_cast<jclass>( local_env->NewGlobalRef( local_class_ref ) ), VirtualMachine::DeleteSharedClass };
	};

	std::shared_ptr<_jclass> VirtualMachine::GetClassReference( const char* class_name )
	{
		JNI_RETURN_IF_E( !IsValid(), {}, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		JNI_RETURN_IF_W( ( class_name == nullptr ) || !strlen( class_name ), {}, "Attempt to get Java class via empty class name." );

		Utils::MutexLock lock{ m_classes_mutex };
		auto& weak_class = m_shared_classes[ class_name ];
		JNI_RETURN_IF_V( !weak_class.expired(), weak_class.lock(), "Shared class found." );

		// If shared class already lost or never been found, ask JNI to lookup it.
		auto shared_class	= LoadClass( class_name );
		weak_class			= shared_class;

		return shared_class;
	};

	std::shared_ptr<_jclass> VirtualMachine::LoadClass( const char* class_name )
	{
		JNI_RETURN_IF_E( !IsValid(), {}, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env			= GetLocalEnvironment();
		jclass local_class_ref	= nullptr;

		if( pthread_self() == m_main_thread_id )
		{
			// For main thread we may use `FindClass` function of `JNIEnv` object.
			local_class_ref	= local_env->FindClass( class_name );
		}
		else
		{
			// Since JNI can't return class reference from native threads,
			// according to next article the best way is using the cached `ClassLoader` instance.
			// https://developer.android.com/training/articles/perf-jni.html#faq_FindClass

			// The name of class must be converted into Java-style package name.
			std::string modified_class_name{ class_name };
			for( char& stored_char : modified_class_name )
			{
				if( stored_char == '/' )
				{
					stored_char = '.';
				};
			};

			// For any other thread only captured `ClassLoader` instance may be used.
			local_class_ref = reinterpret_cast<jclass>(
				local_env->CallObjectMethod( *m_class_loader, *m_load_class_func, Marshaling::ToJava( modified_class_name ) )
			);
		};

		if( local_env->ExceptionCheck() == JNI_TRUE )
		{
			local_env->ExceptionDescribe();
			local_env->ExceptionClear();
			local_class_ref = nullptr;
		};

		JNI_RETURN_IF_W( local_class_ref == nullptr, {}, "No class was found with name `%s`.", class_name );

		// The value returned is `std::shared_ptr` with custom deleter.
		return { reinterpret_cast<jclass>( local_env->NewGlobalRef( local_class_ref ) ), VirtualMachine::DeleteSharedClass };
	};
};

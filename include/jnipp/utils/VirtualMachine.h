// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace Jni
{
	/// @brief	
	class VirtualMachine final
	{
		friend class Class;	// Intensively uses `GetClassReference` functions.
	public:
		constexpr static int32_t JNI_VERSION = JNI_VERSION_1_6;

		/// @brief	Initialize the instance with the given JVM.
		static const bool Initialize( JavaVM* jvm );

		/// @brief	Finalize the instance. All environment instances must be released before this function invoked.
		static void Finalize();

		/// @brief	Register native handlers for Java class via given binding table.
		static const bool RegisterClassNatives( const NativeBindingTable& bindings );

		/// @brief	Register native handlers for list of Java classes via given list of binding tables.
		static const bool RegisterClassNatives( std::initializer_list<NativeBindingTable> bindings );

		/// @brief	Get the `JniEnv` instance for current thread.
		static JNIEnv* GetLocalEnvironment();

		/// @brief	Get the global `JavaVM` instance.
		static inline JavaVM* GetJvm()			{ return GetInstance().m_jvm; };

		/// @brief	Check the `VirtualMachine` is properly initialized.
		static inline const bool IsValid()		{ return GetInstance().m_jvm != nullptr; };

	private:
		/// @brief	Access to single instance (using Meyers's implementation).
		static VirtualMachine& GetInstance();

		/// @brief	Deleter of shared class.
		static void DeleteSharedClass( jclass value );

		/// @brief	Detach thread-local JNIEnv instance from thread.
		static void DetachLocalEnv( void* local_env );

	private:
		VirtualMachine() = default;

		const bool CaptureClassLoader();
		const bool AcquireClassInterface();

		std::shared_ptr<_jclass> GetClassReference( jobject local_object_ref );
		std::shared_ptr<_jclass> GetClassReference( jclass local_class_ref );
		std::shared_ptr<_jclass> GetClassReference( const char* class_name );
		std::shared_ptr<_jclass> LoadClass( const char* class_name );

	private:
		// ['Java class name'] -> weak `jclass` pointer. Used for shared owning of `jclass` instances.
		using WeakClassStorage = std::unordered_map< std::string, std::weak_ptr<_jclass> >;
		
		Utils::Mutex		m_classes_mutex;				// Synchronization mutex for safe multi-thread access to class references.
		JavaVM*				m_jvm				= nullptr;	// Instance of Java virtual machine.
		JNIEnv*				m_main_env			= nullptr;	// Instance of JniEnv for the main thread.
		int64_t				m_main_thread_id	= 0;		// TID of main thread, where the initialization was invoked from.
		int64_t				m_detach_key		= 0;		// ID of thread-local key, which stores the local `JNIEnv` instance.

		WeakClassStorage	m_shared_classes;				// Storage for found Java class descriptors.

	private:
		Object	m_class_loader;

		FunctionHandle<Class, std::string>	m_load_class_func;		// `java.lang.Class java.lang.ClassLoader::loadClass( java.lang.String )`

		FunctionHandle<Class>				m_get_super_class_func;	// `java.lang.Class java.lang.Class::getSuperClass()`
		FunctionHandle<std::string>			m_get_canonical_name;	// `java.lang.String java.lang.Class::getCanonicalName()`
		FunctionHandle<std::string>			m_get_name;				// `java.lang.String java.lang.Class::getName()`
		FunctionHandle<std::string>			m_get_simple_name;		// `java.lang.String java.lang.Class::getSimpleName()`
	};
};

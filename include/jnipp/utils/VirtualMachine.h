// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace jnipp
{
	/// @brief	
	class VirtualMachine final
	{
		friend class ClassHandle;	// 
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
		static JavaVM* GetJvm();

		/// @brief	Check the `VirtualMachine` is properly initialized.
		static const bool IsValid();

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

		std::shared_ptr<_jclass> GetClass( jobject local_object_ref );
		std::shared_ptr<_jclass> GetClass( jclass local_class_ref );
		std::shared_ptr<_jclass> GetClass( const char* class_name );
		std::shared_ptr<_jclass> LookupClass( const char* class_name );

	private:
		// ['Java class name'] -> weak `jclass` pointer. Used for shared owning of `jclass` instances.
		using WeakClassStorage = std::unordered_map< std::string, std::weak_ptr<_jclass> >;
		
		utils::Mutex		m_mutex;						// Synchronization mutex for safe multi-thread access.
		JavaVM*				m_jvm				= nullptr;	// Instance of Java virtual machine.
		JNIEnv*				m_main_env			= nullptr;	// Instance of JniEnv for the main thread.
		int64_t				m_main_thread_id	= 0;		// TID of main thread, where the initialization was invoked from.
		int64_t				m_detach_key		= 0;		// 

		WeakClassStorage	m_shared_classes;				// Storage for found Java class descriptors.

	private:
		ObjectHandle	m_class_loader;

		FunctionHandle<ClassHandle, std::string>	m_load_class_func;
	};
};

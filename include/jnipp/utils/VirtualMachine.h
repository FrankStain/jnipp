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
		/// @brief	Initialize the instance with the given JVM.
		static const bool Initialize( JavaVM* jvm );

		/// @brief	Finalize the instance. All environment instances must be released before this function invoked.
		static void Finalize();

		/// @brief	Register native handlers for Java class via given binding table.
		static const bool RegisterClassNatives( const NativeBindingTable& bindings );

		/// @brief	Register native handlers for list of Java classes via given list of binding tables.
		static const bool RegisterClassNatives( std::initializer_list<NativeBindingTable> bindings );

		/// @brief	
		static JNIEnv* GetLocalEnvironment();

		/// @brief	
		static JNIEnv* GetGlobalEnvironment();

		/// @brief	
		static JavaVM* GetJvm();

		/// @brief	
		static const bool IsValid();

	private:
		static VirtualMachine& GetInstance();

		static void SharedClassDeleter( jclass value );

		VirtualMachine() = default;

	private:
		
	};
};

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	/// @brief	Regular implementation of builder for native function handlers.
	template< typename >
	struct NativeFunctionBuilder;


	/// @brief	Wrapper for native function handler. It used to receive arguments from Java and convert it into native types.
	template< typename TSenderType, typename TNativeReturnType, typename... TNativeArgumentTypes >
	struct NativeFunctionWrapper final
	{
		/// @brief	The native function wrap, which will convert the arguments for origin native function.
		template< TNativeReturnType (*NATIVE_FUNCTION)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... ) >
		static Jni::Marshaling::JavaType<TNativeReturnType> Wrap( JNIEnv* local_env, TSenderType sender, Jni::Marshaling::JavaType<TNativeArgumentTypes>... arguments );
	};


	/// @brief	Wrapper for native function handler. It used to receive arguments from Java and convert it into native types.
	template< typename TSenderType, typename... TNativeArgumentTypes >
	struct NativeFunctionWrapper<TSenderType, void, TNativeArgumentTypes...> final
	{
		/// @brief	The native function wrap, which will convert the arguments for origin native function.
		template< void (*NATIVE_FUNCTION)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... ) >
		static void Wrap( JNIEnv* local_env, TSenderType sender, Jni::Marshaling::JavaType<TNativeArgumentTypes>... arguments );
	};


	/// @brief	Partial specialization of builder for native function handlers. Used to wrap the handler into type-converting wrap.
	template< typename TSenderType, typename TNativeReturnType, typename... TNativeArgumentTypes >
	struct NativeFunctionBuilder<TNativeReturnType (*)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... )> final
	{
		static_assert(
			std::is_same<jobject, TSenderType>::value || std::is_same<jclass, TSenderType>::value,
			"The function handler must be `jobject` or `jclass`."
		);

		/// @brief	Valid JNI function signature for given function pointer.
		using Signature	= FunctionSignature<Jni::Marshaling::TypeSignature<TNativeReturnType>, Jni::Marshaling::TypeSignature<TNativeArgumentTypes>...>;

		/// @brief	Wrapper for given native function.
		using Wrapper	= NativeFunctionWrapper<TSenderType, TNativeReturnType, TNativeArgumentTypes...>;

		/// @brief	Type of function, which will wrap the original function.
		using WrapperFunction = Jni::Marshaling::JavaType<TNativeReturnType> (*)( JNIEnv*, TSenderType, Jni::Marshaling::JavaType<TNativeArgumentTypes>... );

		/// @brief	Factory function for descriptions of native function handlers.
		template< TNativeReturnType (*NATIVE_FUNCTION)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... ) >
		static inline NativeFunction GetNativeFunction( const char* function_name );
	};
}
}

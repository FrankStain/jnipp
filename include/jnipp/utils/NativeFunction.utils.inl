// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	template< typename TSenderType, typename TNativeReturnType, typename... TNativeArgumentTypes >
	template< TNativeReturnType (*NATIVE_FUNCTION)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... ) >
	Jni::Marshaling::JavaType<TNativeReturnType> NativeFunctionWrapper<TSenderType, TNativeReturnType, TNativeArgumentTypes...>::Wrap(
		JNIEnv* local_env,
		TSenderType sender,
		Jni::Marshaling::JavaType<TNativeArgumentTypes>... arguments
	)
	{
		return (Jni::Marshaling::JavaType<TNativeReturnType>)Jni::Marshaling::ToJava<TNativeReturnType>(
			NATIVE_FUNCTION( local_env, sender, Jni::Marshaling::FromJava<TNativeArgumentTypes>( arguments )... )
		);
	}

	template< typename TSenderType, typename... TNativeArgumentTypes >
	template< void (*NATIVE_FUNCTION)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... ) >
	void NativeFunctionWrapper<TSenderType, void, TNativeArgumentTypes...>::Wrap(
		JNIEnv* local_env,
		TSenderType sender,
		Jni::Marshaling::JavaType<TNativeArgumentTypes>... arguments
	)
	{
		NATIVE_FUNCTION( local_env, sender, Jni::Marshaling::FromJava<TNativeArgumentTypes>( arguments )... );
	}

	template< typename TSenderType, typename TNativeReturnType, typename... TNativeArgumentTypes >
	template< TNativeReturnType (*NATIVE_FUNCTION)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... ) >
	inline NativeFunction NativeFunctionBuilder<TNativeReturnType (*)( JNIEnv*, TSenderType, const TNativeArgumentTypes&... )>::GetNativeFunction( const char* function_name )
	{
		WrapperFunction func = &Wrapper::template Wrap<NATIVE_FUNCTION>;
		return {
			reinterpret_cast<void*>( func ),
			Signature::GetString(),
			function_name
		};
	}
}
}

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline StaticFunctionInvocation<TNativeReturnType, TNativeArguments...>::StaticFunctionInvocation( JNIEnv* local_env, jclass class_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_class_ref( class_ref )
		, m_function_id( function_id )
	{
		JNI_EXPECTS( m_class_ref != nullptr );
		JNI_EXPECTS( m_function_id != 0 )
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType StaticFunctionInvocation<TNativeReturnType, TNativeArguments...>::Call( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeReturnType, TNativeArguments...>::RESULT;
		
		JNI_RETURN_IF_E( m_local_env == nullptr, {}, "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		JNI_RETURN_IF_E(
			LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ),
			{},
			"Failed to push JVM local frame with size %d.",
			LOCAL_FRAME_SIZE
		);

		auto function_result = (JavaType)(m_local_env->*FUNCTION_HANDLER)( m_class_ref, m_function_id, Jni::Marshaling::ToJava( arguments )... );

		TNativeReturnType native_result;
		Jni::Marshaling::FromJava( function_result, native_result );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, native_result );
		m_local_env->PopLocalFrame( nullptr );
		return native_result;
	};

	template< typename... TNativeArguments >
	inline StaticFunctionInvocation<void, TNativeArguments...>::StaticFunctionInvocation( JNIEnv* local_env, jclass class_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_class_ref( class_ref )
		, m_function_id( function_id )
	{
		JNI_EXPECTS( m_class_ref != nullptr );
		JNI_EXPECTS( m_function_id != 0 )
	};

	template< typename... TNativeArguments >
	inline void StaticFunctionInvocation<void, TNativeArguments...>::Call( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeArguments...>::RESULT;
		
		JNI_RETURN_IF_E( m_local_env == nullptr, , "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		JNI_RETURN_IF_E(
			LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ),
			,
			"Failed to push JVM local frame with size %d.",
			LOCAL_FRAME_SIZE
		);

		(m_local_env->*FUNCTION_HANDLER)( m_class_ref, m_function_id, Jni::Marshaling::ToJava( arguments )... );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0 );
		m_local_env->PopLocalFrame( nullptr );
	};
};
};

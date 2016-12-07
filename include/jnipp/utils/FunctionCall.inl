// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace utils
{
	template< size_t... NUMBERS >
	struct NumberSumm;

	template< size_t NUMBER, size_t... REST_NUMBERS >
	struct NumberSumm<NUMBER, REST_NUMBERS...>
	{
		constexpr static const size_t RESULT = NUMBER + NumberSumm<REST_NUMBERS...>::RESULT;
	};

	template< size_t NUMBER >
	struct NumberSumm<NUMBER>
	{
		constexpr static const size_t RESULT = NUMBER;
	};

	template<>
	struct NumberSumm<>
	{
		constexpr static const size_t RESULT = 0;
	};

	template< typename... TNativeTypes >
	struct TotalLocalFrame : NumberSumm<jnipp::marshaling::JniEnvFacade<TNativeTypes>::LOCAL_FRAME_SIZE...>
	{
	
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline FunctionCall<TNativeReturnType, TNativeArguments...>::FunctionCall( JNIEnv* local_env, jobject object_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_object_ref( object_ref )
		, m_function_id( function_id )
	{
		Expects( m_object_ref != nullptr );
		Expects( m_function_id != 0 );
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionCall<TNativeReturnType, TNativeArguments...>::Call( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeReturnType, TNativeArguments...>::RESULT;
		
		CRET_E( m_local_env == nullptr, {}, "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		CRET_E( LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), {}, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		auto function_result = reinterpret_cast<JavaType>(
			(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, jnipp::marshaling::ToJava( arguments )... )
		);

		TNativeReturnType native_result;
		jnipp::marshaling::FromJava( function_result, native_result );

		CRET( LOCAL_FRAME_SIZE == 0, native_result );
		m_local_env->PopLocalFrame( nullptr );
		return native_result;
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionCall<TNativeReturnType, TNativeArguments...>::CallNonVirtual( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeReturnType, TNativeArguments...>::RESULT;
		
		CRET_E( m_local_env == nullptr, {}, "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		CRET_E( LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), {}, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		auto function_result = reinterpret_cast<JavaType>(
			(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)( m_object_ref, m_function_id, jnipp::marshaling::ToJava( arguments )... )
		);

		TNativeReturnType native_result;
		jnipp::marshaling::FromJava( function_result, native_result );

		CRET( LOCAL_FRAME_SIZE == 0, native_result );
		m_local_env->PopLocalFrame( nullptr );
		return native_result;
	};

	template< typename... TNativeArguments >
	inline FunctionCall<void, TNativeArguments...>::FunctionCall( JNIEnv* local_env, jobject object_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_object_ref( object_ref )
		, m_function_id( function_id )
	{
		Expects( m_object_ref != nullptr );
		Expects( m_function_id != 0 )
	};

	template< typename... TNativeArguments >
	inline void FunctionCall<void, TNativeArguments...>::Call( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeArguments...>::RESULT;
		
		CRET_E( m_local_env == nullptr, , "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		CRET_E( LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), , "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, jnipp::marshaling::ToJava( arguments )... );

		CRET( LOCAL_FRAME_SIZE == 0 );
		m_local_env->PopLocalFrame( nullptr );
	};

	template< typename... TNativeArguments >
	inline void FunctionCall<void, TNativeArguments...>::CallNonVirtual( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeArguments...>::RESULT;
		
		CRET_E( m_local_env == nullptr, , "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		CRET_E( LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), , "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)( m_object_ref, m_function_id, jnipp::marshaling::ToJava( arguments )... );

		CRET( LOCAL_FRAME_SIZE == 0 );
		m_local_env->PopLocalFrame( nullptr );
	};
};
};

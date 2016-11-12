// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace utils
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline StaticFunctionCall<TNativeReturnType, TNativeArguments>::StaticFunctionCall( JNIEnv* local_env, jclass class_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_class_ref( object_ref )
		, m_function_id( function_id )
	{
		Expects( m_class_ref != nullptr );
		Expects( m_function_id != 0 )
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType StaticFunctionCall<TNativeReturnType, TNativeArguments>::Call( TNativeArguments... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeReturnType, TNativeArguments...>::RESULT;
		
		CRET_E( m_local_env == nullptr, {}, "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		CRET_E( LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), false, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		auto function_result = reinterpret_cast<JavaType>(
			(m_local_env->*FUNCTION_HANDLER)( m_class_ref, m_function_id, jnipp::marshaling::ToJava( std::forward<TNativeArguments>( arguments ) )... );
		);

		TNativeReturnType native_result;
		jnipp::marshaling::FromJava( function_result, native_result );

		CRET( LOCAL_FRAME_SIZE == 0, native_result );
		local_env->PopLocalFrame( nullptr );
		return native_result;
	};

	template< typename... TNativeArguments >
	inline StaticFunctionCall<void, TNativeArguments>::StaticFunctionCall( JNIEnv* local_env, jclass class_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_class_ref( object_ref )
		, m_function_id( function_id )
	{
		Expects( m_class_ref != nullptr );
		Expects( m_function_id != 0 )
	};

	template< typename... TNativeArguments >
	inline void StaticFunctionCall<void, TNativeArguments>::Call( TNativeArguments... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeArguments...>::RESULT;
		
		CRET_E( m_local_env == nullptr, {}, "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		CRET_E( LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), false, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		(m_local_env->*FUNCTION_HANDLER)( m_class_ref, m_function_id, jnipp::marshaling::ToJava( std::forward<TNativeArguments>( arguments ) )... );

		CRET( LOCAL_FRAME_SIZE == 0, native_result );
		local_env->PopLocalFrame( nullptr );
	};
};
};

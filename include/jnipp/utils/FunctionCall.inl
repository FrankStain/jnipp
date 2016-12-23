// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
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
	struct TotalLocalFrame : NumberSumm<Jni::Marshaling::JniEnvFacade<TNativeTypes>::LOCAL_FRAME_SIZE...>
	{
	
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline MemberFunctionInvocation<TNativeReturnType, TNativeArguments...>::MemberFunctionInvocation( JNIEnv* local_env, jobject object_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_function_id( function_id )
		, m_object_ref( object_ref )
	{
		JNI_EXPECTS( m_object_ref != nullptr );
		JNI_EXPECTS( m_function_id != nullptr );
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType MemberFunctionInvocation<TNativeReturnType, TNativeArguments...>::Call( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeReturnType, TNativeArguments...>::RESULT;

		JNI_RETURN_IF_E( m_local_env == nullptr, {}, "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		JNI_RETURN_IF_E(
			LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ),
			{},
			"Failed to push JVM local frame with size %d.",
			LOCAL_FRAME_SIZE
		);

		auto function_result = (JavaType)(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, Jni::Marshaling::ToJava( arguments )... );
		TNativeReturnType native_result;
		Jni::Marshaling::FromJava( function_result, native_result );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, native_result );
		m_local_env->PopLocalFrame( nullptr );
		return native_result;
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType MemberFunctionInvocation<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		jclass class_ref,
		const TNativeArguments&... arguments
	) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeReturnType, TNativeArguments...>::RESULT;

		JNI_EXPECTS( class_ref != nullptr );
		JNI_RETURN_IF_E( m_local_env == nullptr, {}, "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		JNI_RETURN_IF_E(
			LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ),
			{},
			"Failed to push JVM local frame with size %d.",
			LOCAL_FRAME_SIZE
		);

		auto function_result = (JavaType)(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)(
			m_object_ref,
			class_ref,
			m_function_id,
			Jni::Marshaling::ToJava( arguments )...
		);

		TNativeReturnType native_result;
		Jni::Marshaling::FromJava( function_result, native_result );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, native_result );
		m_local_env->PopLocalFrame( nullptr );
		return native_result;
	};

	template< typename... TNativeArguments >
	inline MemberFunctionInvocation<void, TNativeArguments...>::MemberFunctionInvocation( JNIEnv* local_env, jobject object_ref, jmethodID function_id )
		: m_local_env( local_env )
		, m_function_id( function_id )
		, m_object_ref( object_ref )
	{
		JNI_EXPECTS( m_object_ref != nullptr );
		JNI_EXPECTS( m_function_id != nullptr )
	};

	template< typename... TNativeArguments >
	inline void MemberFunctionInvocation<void, TNativeArguments...>::Call( const TNativeArguments&... arguments ) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeArguments...>::RESULT;

		JNI_RETURN_IF_E( m_local_env == nullptr, , "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		JNI_RETURN_IF_E(
			LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ),
			,
			"Failed to push JVM local frame with size %d.",
			LOCAL_FRAME_SIZE
		);

		(m_local_env->*FUNCTION_HANDLER)( m_object_ref, m_function_id, Jni::Marshaling::ToJava( arguments )... );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0 );
		m_local_env->PopLocalFrame( nullptr );
	};

	template< typename... TNativeArguments >
	inline void MemberFunctionInvocation<void, TNativeArguments...>::CallNonVirtual(
		jclass class_ref,
		const TNativeArguments&... arguments
	) const
	{
		constexpr const size_t LOCAL_FRAME_SIZE = TotalLocalFrame<TNativeArguments...>::RESULT;

		JNI_EXPECTS( class_ref != nullptr );
		JNI_RETURN_IF_E( m_local_env == nullptr, , "%s:%d - Attempt to call function while local JNI environment not initialized.", __func__, __LINE__ );
		JNI_RETURN_IF_E(
			LOCAL_FRAME_SIZE && ( m_local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ),
			,
			"Failed to push JVM local frame with size %d.",
			LOCAL_FRAME_SIZE
		);

		(m_local_env->*NONVIRTUAL_FUNCTION_HANDLER)(
			m_object_ref,
			class_ref,
			m_function_id,
			Jni::Marshaling::ToJava( arguments )...
		);

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0 );
		m_local_env->PopLocalFrame( nullptr );
	};
};
};

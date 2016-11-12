// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace utils
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	class StaticFunctionCall
	{
	public:
		inline StaticFunctionCall( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		inline TNativeReturnType Call( TNativeArguments... arguments ) const;

	private:
		using JavaType	= typename jnipp::marshaling::JniEnvFacade<TNativeReturnType>::JavaType;

	private:
		constexpr static auto FUNCTION_HANDLER	= marshaling::JniEnvFacade<TNativeType>::STATIC_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jclass		m_class_ref		= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};

	template< typename... TNativeArguments >
	class StaticFunctionCall<void, TNativeArguments...>
	{
	public:
		inline StaticFunctionCall( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		inline TNativeReturnType Call( TNativeArguments... arguments ) const;

	private:
		constexpr static auto FUNCTION_HANDLER	= marshaling::JniEnvFacade<void>::STATIC_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jclass		m_class_ref		= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};
};
};

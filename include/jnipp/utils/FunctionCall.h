// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace utils
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	class FunctionCall
	{
	public:
		inline FunctionCall( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		inline TNativeReturnType Call( TNativeArguments... arguments ) const;
		inline TNativeReturnType CallNonVirtual( TNativeArguments... arguments ) const;

	private:
		using JavaType	= typename jnipp::marshaling::JniEnvFacade<TNativeReturnType>::JavaType;

	private:
		constexpr static auto FUNCTION_HANDLER				= marshaling::JniEnvFacade<TNativeType>::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= marshaling::JniEnvFacade<TNativeType>::NONVIRTUAL_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};

	template< typename... TNativeArguments >
	class FunctionCall<void, TNativeArguments...>
	{
	public:
		inline FunctionCall( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		inline void Call( TNativeArguments... arguments ) const;
		inline void CallNonVirtual( TNativeArguments... arguments ) const;

	private:
		constexpr static auto FUNCTION_HANDLER				= marshaling::JniEnvFacade<void>::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= marshaling::JniEnvFacade<void>::NONVIRTUAL_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};
};
};

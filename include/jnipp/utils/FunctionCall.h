// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace utils
{
	/// @brief	Java object method decorator. Used by `FunctionHandle` to directly call the Java method.
	template< typename TNativeReturnType, typename... TNativeArguments >
	class FunctionCall
	{
	public:
		inline FunctionCall( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java object with given function arguments.
		inline TNativeReturnType Call( const TNativeArguments&... arguments ) const;
		
		/// @brief	Call the non-virtual Java method on given Java object with given function arguments.
		inline TNativeReturnType CallNonVirtual( const TNativeArguments&... arguments ) const;

	private:
		/// @brief	Java type of function call result.
		using JavaType	= typename jnipp::marshaling::JniEnvFacade<TNativeReturnType>::JavaType;

	private:
		constexpr static auto FUNCTION_HANDLER				= marshaling::JniEnvFacade<TNativeReturnType>::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= marshaling::JniEnvFacade<TNativeReturnType>::NONVIRTUAL_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};

	/// @brief	Private specialization of Java object method decorator for case of `void` call result.
	template< typename... TNativeArguments >
	class FunctionCall<void, TNativeArguments...>
	{
	public:
		inline FunctionCall( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java object with given function arguments.
		inline void Call( const TNativeArguments&... arguments ) const;
		
		/// @brief	Call the non-virtual Java method on given Java object with given function arguments.
		inline void CallNonVirtual( const TNativeArguments&... arguments ) const;

	private:
		constexpr static auto FUNCTION_HANDLER				= marshaling::JniEnvFacade<void>::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= marshaling::JniEnvFacade<void>::NONVIRTUAL_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};
};
};

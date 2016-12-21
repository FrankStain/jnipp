// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	/// @brief	Java static method decorator. Used by `StaticFunction` to directly call the Java method.
	template< typename TNativeReturnType, typename... TNativeArguments >
	class StaticFunctionCall
	{
	public:
		inline StaticFunctionCall( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java class with given function arguments.
		inline TNativeReturnType Call( const TNativeArguments&... arguments ) const;

	private:
		/// @brief	Java type of function call result.
		using JavaType	= typename Jni::Marshaling::JniEnvFacade<TNativeReturnType>::JavaType;

	private:
		constexpr static auto FUNCTION_HANDLER	= Marshaling::JniEnvFacade<TNativeReturnType>::STATIC_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jclass		m_class_ref		= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};

	/// @brief	Private specialization of Java static method decorator for case of `void` call result.
	template< typename... TNativeArguments >
	class StaticFunctionCall<void, TNativeArguments...>
	{
	public:
		inline StaticFunctionCall( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java class with given function arguments.
		inline void Call( const TNativeArguments&... arguments ) const;

	private:
		constexpr static auto FUNCTION_HANDLER	= Marshaling::JniEnvFacade<void>::STATIC_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jclass		m_class_ref		= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};
};
};

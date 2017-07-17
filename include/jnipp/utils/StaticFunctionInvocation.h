// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	/// @brief	Invocation of Java static function. Directly used by `MemberFunction` to invoke the Java code.
	template< typename TNativeReturnType, typename... TNativeArguments >
	class StaticFunctionInvocation
	{
	public:
		inline StaticFunctionInvocation( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java class with given function arguments.
		inline TNativeReturnType Call( const TNativeArguments&... arguments ) const;

	private:
		/// @brief	Java type of function call result.
		using JavaType	= typename Jni::Marshaling::JavaType<TNativeReturnType>;

	private:
		constexpr static auto FUNCTION_HANDLER	= Jni::Marshaling::NativeTypeTraits<TNativeReturnType>::STATIC_FUNCTION_HANDLER;

		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jclass		m_class_ref		= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};

	/// @brief	Invocation of Java static function with `void` result type. Directly used by `MemberFunction` to invoke the Java code.
	template< typename... TNativeArguments >
	class StaticFunctionInvocation<void, TNativeArguments...>
	{
	public:
		inline StaticFunctionInvocation( JNIEnv* local_env, jclass class_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java class with given function arguments.
		inline void Call( const TNativeArguments&... arguments ) const;

	private:
		constexpr static auto FUNCTION_HANDLER	= Jni::Marshaling::NativeTypeTraits<void>::STATIC_FUNCTION_HANDLER;

		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jclass		m_class_ref		= nullptr;	// Reference to Java object.
		jmethodID	m_function_id	= 0;		// Id of function.
	};
}
}

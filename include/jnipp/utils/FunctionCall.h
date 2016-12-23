// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	/// @brief	Invocation of Java member-function. Directly used by `MemberFunction` to invoke the Java code.
	template< typename TNativeReturnType, typename... TNativeArguments >
	class MemberFunctionInvocation
	{
	public:
		inline MemberFunctionInvocation( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java object with given function arguments.
		inline TNativeReturnType Call( const TNativeArguments&... arguments ) const;
		
		/// @brief	Call the non-virtual Java method on given Java object with given function arguments.
		inline TNativeReturnType CallNonVirtual( jclass class_ref, const TNativeArguments&... arguments ) const;

	private:
		/// @brief	Java type of function call result.
		using JavaType	= typename Jni::Marshaling::JniEnvFacade<TNativeReturnType>::JavaType;

	private:
		constexpr static auto FUNCTION_HANDLER				= Marshaling::JniEnvFacade<TNativeReturnType>::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= Marshaling::JniEnvFacade<TNativeReturnType>::NONVIRTUAL_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jmethodID	m_function_id	= nullptr;	// Id of function.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
	};

	/// @brief	Invocation of Java member-function with `void` result type. Directly used by `MemberFunction` to invoke the Java code.
	template< typename... TNativeArguments >
	class MemberFunctionInvocation<void, TNativeArguments...>
	{
	public:
		inline MemberFunctionInvocation( JNIEnv* local_env, jobject object_ref, jmethodID function_id );

		/// @brief	Call the Java method on given Java object with given function arguments.
		inline void Call( const TNativeArguments&... arguments ) const;
		
		/// @brief	Call the non-virtual Java method on given Java object with given function arguments.
		inline void CallNonVirtual( jclass class_ref, const TNativeArguments&... arguments ) const;

	private:
		constexpr static auto FUNCTION_HANDLER				= Marshaling::JniEnvFacade<void>::FUNCTION_HANDLER;
		constexpr static auto NONVIRTUAL_FUNCTION_HANDLER	= Marshaling::JniEnvFacade<void>::NONVIRTUAL_FUNCTION_HANDLER;
		
		JNIEnv*		m_local_env		= nullptr;	// Current thread-local JNI environment.
		jmethodID	m_function_id	= nullptr;	// Id of function.
		jobject		m_object_ref	= nullptr;	// Reference to Java object.
	};
};
};

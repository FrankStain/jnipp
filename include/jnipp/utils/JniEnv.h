// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/**
		@brief		JNI Environment instance wrap for thread-local environment.
		@note		Instances of `JniEnv` may not be stored in global memory.
		@warning	Instances of `JniEnv` may not be used across the threads.

		`JniEnv` instance represents the thread-local environment of JNI.
	*/
	class JniEnv final
	{
	public:
		template< typename TNativeType >
		inline const bool GetValue( const FieldHandle<TNativeType>& field_handle, TNativeType& value_storage ) const;

		template< typename TNativeType >
		inline const bool GetValue( const StaticFieldHandle<TNativeType>& field_handle, TNativeType& value_storage ) const;

		template< typename TNativeType >
		inline const bool SetValue( const FieldHandle<TNativeType>& field_handle, const TNativeType& value_storage ) const;

		template< typename TNativeType >
		inline const bool SetValue( const StaticFieldHandle<TNativeType>& field_handle, const TNativeType& value_storage ) const;

		template< typename TNativeReturnType, typename... TNativeArguments >
		inline TNativeReturnType Call(
			const FunctionHandle<TNativeReturnType, TNativeArguments...>& function_handle,
			const ObjectHandle& object_handle,
			const TNativeArguments&... arguments
		);

		template< typename TNativeReturnType, typename... TNativeArguments >
		inline TNativeReturnType CallNonVirtual(
			const FunctionHandle<TNativeReturnType, TNativeArguments...>& function_handle,
			const ObjectHandle& object_handle,
			const TNativeArguments&... arguments
		);

		template< typename TNativeReturnType, typename... TNativeArguments >
		inline TNativeReturnType Call(
			const StaticFunctionHandle<TNativeReturnType, TNativeArguments...>& function_handle,
			const ObjectHandle& object_handle,
			const TNativeArguments&... arguments
		);

		inline JNIEnv* operator -> () const	{ return m_local_env; };

	private:
		JniEnv( const JniEnv& )					= delete;
		JniEnv( JniEnv&& )						= delete;

		JniEnv& operator = ( const JniEnv& )	= delete;
		JniEnv& operator = ( JniEnv&& )			= delete;

	private:
		JNIEnv*	m_local_env	= VirtualMachine::GetLocalEnvironment();
	};
};

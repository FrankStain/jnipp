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
		template< typename TDesiredType, typename TGivenType >
		using EnableConvertible = typename std::enable_if<std::is_convertible<TGivenType, TDesiredType>::value>::type;

		template< bool... FLAGS >
		struct FlagsContainer;

		template< bool... FLAGS >
		using TrueFlags = std::is_same< FlagsContainer<FLAGS..., true>, FlagsContainer<true, FLAGS...> >;

	public:
		JniEnv() = default;

		/// @brief	Get the value of field belongs to object using the local JNI environment.
		template< typename TNativeType, typename TValueType, typename = EnableConvertible<TNativeType, TValueType> >
		inline const bool GetValue(
			const FieldHandle<TNativeType>& field_handle,
			const ObjectHandle& object_handle,
			TValueType& value_storage
		) const;

		/// @brief	Get the value of static field using the local JNI environment.
		template< typename TNativeType, typename TValueType, typename = EnableConvertible<TNativeType, TValueType> >
		inline const bool GetValue( const StaticFieldHandle<TNativeType>& field_handle, TValueType& value_storage ) const;

		/// @brief	Set the value of field belongs to object using the local JNI environment.
		template< typename TNativeType, typename TValueType, typename = EnableConvertible<TNativeType, TValueType> >
		inline const bool SetValue(
			const FieldHandle<TNativeType>& field_handle,
			const ObjectHandle& object_handle,
			const TValueType& value_storage
		) const;

		/// @brief	Set the value of static field using the local JNI environment.
		template< typename TNativeType, typename TValueType, typename = EnableConvertible<TNativeType, TValueType> >
		inline const bool SetValue( const StaticFieldHandle<TNativeType>& field_handle, const TValueType& value_storage ) const;

		/// @brief	Call the member function on object using the local JNI environment.
		template<
			typename TNativeReturnType, typename... TNativeArguments, typename... TValueArguments,
			typename = typename std::enable_if< TrueFlags< std::is_convertible<TValueArguments, TNativeArguments>::value... >::value >::type
		>
		inline TNativeReturnType Call(
			const FunctionHandle<TNativeReturnType, TNativeArguments...>& function_handle,
			const ObjectHandle& object_handle,
			const TValueArguments&... arguments
		);

		/// @brief	Call the member function non-virtually on object using the local JNI environment.
		template<
			typename TNativeReturnType, typename... TNativeArguments, typename... TValueArguments,
			typename = typename std::enable_if<TrueFlags< std::is_convertible<TValueArguments, TNativeArguments>::value... >::value>::type
		>
		inline TNativeReturnType CallNonVirtual(
			const FunctionHandle<TNativeReturnType, TNativeArguments...>& function_handle,
			const ObjectHandle& object_handle,
			const TValueArguments&... arguments
		);

		/// @brief	Call the static function using the local JNI environment.
		template<
			typename TNativeReturnType, typename... TNativeArguments, typename... TValueArguments,
			typename = typename std::enable_if<TrueFlags< std::is_convertible<TValueArguments, TNativeArguments>::value... >::value>::type
		>
		inline TNativeReturnType Call(
			const StaticFunctionHandle<TNativeReturnType, TNativeArguments...>& function_handle,
			const TValueArguments&... arguments
		);

		inline const bool IsValid() const				{ return m_local_env != nullptr; };

		inline JNIEnv* operator -> () const				{ return m_local_env; };
		inline explicit operator const bool () const	{ return IsValid(); };

	private:
		JniEnv( const JniEnv& )					= delete;
		JniEnv( JniEnv&& )						= delete;

		JniEnv& operator = ( const JniEnv& )	= delete;
		JniEnv& operator = ( JniEnv&& )			= delete;

	private:
		JNIEnv*	m_local_env	= VirtualMachine::GetLocalEnvironment();
	};
};

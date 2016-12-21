// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TNativeType, typename TValueType, typename >
	inline const bool JniEnv::GetValue(
		const MemberField<TNativeType>& field_handle,
		const Object& object_handle,
		TValueType& value_storage
	) const
	{
		return field_handle.GetValue( m_local_env, object_handle, value_storage );
	};

	template< typename TNativeType, typename TValueType, typename >
	inline const bool JniEnv::GetValue( const StaticField<TNativeType>& field_handle, TValueType& value_storage ) const
	{
		return field_handle.GetValue( m_local_env, value_storage );
	};

	template< typename TNativeType, typename TValueType, typename >
	inline const bool JniEnv::SetValue(
		const MemberField<TNativeType>& field_handle,
		const Object& object_handle,
		const TValueType& value_storage
	) const
	{
		return field_handle.SetValue( m_local_env, object_handle, value_storage );
	};

	template< typename TNativeType, typename TValueType, typename >
	inline const bool JniEnv::SetValue( const StaticField<TNativeType>& field_handle, const TValueType& value_storage ) const
	{
		return field_handle.SetValue( m_local_env, value_storage );
	};

	template< typename TNativeReturnType, typename... TNativeArguments, typename... TValueArguments, typename >
	inline TNativeReturnType JniEnv::Call(
		const MemberFunction<TNativeReturnType, TNativeArguments...>& function_handle,
		const Object& object_handle,
		const TValueArguments&... arguments
	)
	{
		return function_handle.Call( m_local_env, object_handle, arguments... );
	};

	template< typename TNativeReturnType, typename... TNativeArguments, typename... TValueArguments, typename >
	inline TNativeReturnType JniEnv::CallNonVirtual(
		const MemberFunction<TNativeReturnType, TNativeArguments...>& function_handle,
		const Object& object_handle,
		const TValueArguments&... arguments
	)
	{
		return function_handle.CallNonVirtual( m_local_env, object_handle, arguments... );
	};

	template< typename TNativeReturnType, typename... TNativeArguments, typename... TValueArguments, typename >
	inline TNativeReturnType JniEnv::Call(
		const StaticFunction<TNativeReturnType, TNativeArguments...>& function_handle,
		const TValueArguments&... arguments
	)
	{
		return function_handle.Call( m_local_env, arguments... );
	};
};

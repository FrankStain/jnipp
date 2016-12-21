// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const FunctionHandle& other )
		: m_function_id( other.m_function_id )
	{
	
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( FunctionHandle&& other )
		: m_function_id( std::move( other.m_function_id ) )
	{
	
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const std::string& class_name, const std::string& function_name )
		: FunctionHandle( class_name.c_str(), function_name.c_str() )
	{
	
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const Class& class_handle, const std::string& function_name )
		: FunctionHandle( *class_handle, function_name.c_str() )
	{
	
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const char* class_name, const char* function_name )
		: FunctionHandle( Class{ class_name }, function_name )
	{
	
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const Class& class_handle, const char* function_name )
		: m_class_handle( class_handle )
	{
		JNI_EXPECTS( m_class_handle );
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env	= VirtualMachine::GetLocalEnvironment();
		m_function_id	= local_env->GetMethodID( *m_class_handle, function_name, Signature::GetString() );

		JNI_ENSURES( m_function_id != 0 );
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::Call(
		const Object& object_handle,
		const TNativeArguments&... arguments
	) const
	{
		return Call( *object_handle, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::Call( jobject object_ref, const TNativeArguments&... arguments ) const
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), TNativeReturnType(), "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return Call( local_env, object_ref, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::Call(
		JNIEnv* local_env,
		const Object& object_handle,
		const TNativeArguments&... arguments
	) const
	{
		return Call( local_env, *object_handle, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::Call(
		JNIEnv* local_env,
		jobject object_ref,
		const TNativeArguments&... arguments
	) const
	{
		JNI_RETURN_IF_E( !IsValid(), TNativeReturnType(), "Function handle was not initialized properly." );
		JNI_RETURN_IF_E( object_ref == nullptr, TNativeReturnType(), "Attempt to call member function of null object." );

		return CallDecorator{ local_env, object_ref, m_function_id }.Call( arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		const Object& object_handle,
		const TNativeArguments&... arguments
	) const
	{
		return CallNonVirtual( *object_handle, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		jobject object_ref,
		const TNativeArguments&... arguments
	) const
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), TNativeReturnType(), "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return CallNonVirtual( local_env, object_ref, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		JNIEnv* local_env,
		const Object& object_handle,
		const TNativeArguments&... arguments
	) const
	{
		return CallNonVirtual( local_env, *object_handle, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		JNIEnv* local_env,
		jobject object_ref,
		const TNativeArguments&... arguments
	) const
	{
		JNI_RETURN_IF_E( !IsValid(), TNativeReturnType(), "Function handle was not initialized properly." );
		JNI_RETURN_IF_E( object_ref == nullptr, TNativeReturnType(), "Attempt to call member function of null object." );

		return CallDecorator{ local_env, object_ref, m_function_id }.CallNonVirtual( *m_class_handle, arguments... );
	};
};

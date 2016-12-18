// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
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
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const ClassHandle& class_handle, const std::string& function_name )
		: FunctionHandle( *class_handle, function_name.c_str() )
	{
	
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const char* class_name, const char* function_name )
		: FunctionHandle( ClassHandle{ class_name }, function_name )
	{
	
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( const ClassHandle& class_handle, const char* function_name )
		: FunctionHandle( *class_handle, function_name )
	{
	
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	FunctionHandle<TNativeReturnType, TNativeArguments...>::FunctionHandle( jclass class_ref, const char* function_name )
	{
		Expects( class_ref != nullptr );
		CRET_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env	= VirtualMachine::GetLocalEnvironment();
		m_function_id	= local_env->GetMethodID( class_ref, function_name, Signature::GetString() );

		Ensures( m_function_id != 0 );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::Call(
		const ObjectHandle& object_handle,
		const TNativeArguments&... arguments
	) const
	{
		return Call( *object_handle, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::Call( jobject object_ref, const TNativeArguments&... arguments ) const
	{
		CRET_E( !VirtualMachine::IsValid(), TNativeReturnType(), "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return Call( local_env, object_ref, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::Call(
		JNIEnv* local_env,
		const ObjectHandle& object_handle,
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
		CRET_E( !IsValid(), TNativeReturnType(), "Function handle was not initialized properly." );
		CRET_E( object_ref == nullptr, TNativeReturnType(), "Attempt to call member function of null object." );

		return CallDecorator{ local_env, object_ref, m_function_id }.Call( arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		const ObjectHandle& object_handle,
		const ClassHandle& class_handle,
		const TNativeArguments&... arguments
	) const
	{
		return CallNonVirtual( *object_handle, *class_handle, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		jobject object_ref,
		jclass class_ref,
		const TNativeArguments&... arguments
	) const
	{
		CRET_E( !VirtualMachine::IsValid(), TNativeReturnType(), "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return CallNonVirtual( local_env, object_ref, class_ref, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		JNIEnv* local_env,
		const ObjectHandle& object_handle,
		const ClassHandle& class_handle,
		const TNativeArguments&... arguments
	) const
	{
		return CallNonVirtual( local_env, *object_handle, *class_handle, arguments... );
	};
		
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType FunctionHandle<TNativeReturnType, TNativeArguments...>::CallNonVirtual(
		JNIEnv* local_env,
		jobject object_ref,
		jclass class_ref,
		const TNativeArguments&... arguments
	) const
	{
		CRET_E( !IsValid(), TNativeReturnType(), "Function handle was not initialized properly." );
		CRET_E( object_ref == nullptr, TNativeReturnType(), "Attempt to call member function of null object." );

		return CallDecorator{ local_env, object_ref, m_function_id }.CallNonVirtual( class_ref, arguments... );
	};
};

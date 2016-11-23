// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::StaticFunctionHandle( const StaticFunctionHandle& other )
		: m_class_handle( other.m_class_handle )
		, m_function_id( other.m_function_id )
	{

	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::StaticFunctionHandle( StaticFunctionHandle&& other )
		: m_class_handle( std::move( other.m_class_handle ) )
		, m_function_id( std::move( other.m_function_id ) )
	{

	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::StaticFunctionHandle( const std::string& class_name, const std::string& function_name )
		: StaticFunctionHandle( class_name.c_str(), function_name.c_str() )
	{

	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::StaticFunctionHandle( const ClassHandle& class_handle, const std::string& function_name )
		: StaticFunctionHandle( class_handle, function_name.c_str() )
	{

	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::StaticFunctionHandle( const char* class_name, const char* function_name )
		: StaticFunctionHandle( ClassHandle{ class_name }, function_name )
	{

	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::StaticFunctionHandle( const ClassHandle& class_handle, const char* function_name )
		: m_class_handle( class_handle )
	{
		Expects( m_class_handle.IsValid() );
		CRET_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env	= VirtualMachine::GetLocalEnvironment();
		m_function_id	= local_env->GetStaticMethodID( *m_class_handle, function_name, Signature::GetString() );

		Ensures( m_function_id != 0 );
	};

	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::Call( const ObjectHandle& object_handle, const TNativeArguments&... arguments ) const
	{
		CRET_E( !VirtualMachine::IsValid(), TNativeReturnType{}, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return Call( local_env, arguments... );
	};
	
	template< typename TNativeReturnType, typename... TNativeArguments >
	inline TNativeReturnType StaticFunctionHandle<TNativeReturnType, TNativeArguments...>::Call( JNIEnv* local_env, const TNativeArguments&... arguments ) const
	{
		CRET_E( !IsValid(), TNativeReturnType{}, "Function handle was not initialized properly." );

		return CallDecorator{ local_env, *m_class_handle, m_function_id }.Call( arguments... );
	};
};

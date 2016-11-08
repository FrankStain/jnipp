// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	template< typename TNativeType >
	StaticFieldHandle<TNativeType>::StaticFieldHandle( const StaticFieldHandle& other )
		: m_class_handle( other.m_class_handle )
		, m_field_id( other.m_field_id )
	{
	
	};

	template< typename TNativeType >
	StaticFieldHandle<TNativeType>::StaticFieldHandle<TNativeType>::StaticFieldHandle( StaticFieldHandle&& other )
		: m_class_handle( td::move( other.m_class_handle ) )
		, m_field_id( std::move( other.m_field_id ) )
	{
	
	};
	
	template< typename TNativeType >
	StaticFieldHandle<TNativeType>::StaticFieldHandle( const std::string& class_name, const std::string& field_name )
		: StaticFieldHandle( class_name.c_str(), field_name.c_str() )
	{
	
	};
	
	template< typename TNativeType >
	StaticFieldHandle<TNativeType>::StaticFieldHandle( const ClassHandle& class_handle, const std::string& field_name )
		: StaticFieldHandle( class_handle, field_name.c_str() )
	{
	
	};
	
	template< typename TNativeType >
	StaticFieldHandle<TNativeType>::StaticFieldHandle( const char* class_name, const char* field_name )
		: StaticFieldHandle( ClassHandle{ class_name }, field_name )
	{
	
	};
	
	template< typename TNativeType >
	StaticFieldHandle<TNativeType>::StaticFieldHandle( const ClassHandle& class_handle, const char* field_name )
		: m_class_handle( class_handle )
	{
		Expects( m_class_handle.IsValid() );
		CRET_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env	= VirtualMachine::GetLocalEnvironment();
		m_field_id		= local_env->GetFieldID( class_ref, field_name, Signature::GetString() );

		Ensures( m_field_id != 0 );
	};
		
	template< typename TNativeType >
	inline const bool StaticFieldHandle<TNativeType>::GetValue( TFieldType& value_storage ) const
	{
	
	};
		
	template< typename TNativeType >
	inline const bool StaticFieldHandle<TNativeType>::SetValue( const TFieldType& value_storage ) const
	{
	
	};
		
	template< typename TNativeType >
	inline const bool StaticFieldHandle<TNativeType>::GetValue( JNIEnv* local_env, TFieldType& value_storage ) const
	{
	
	};
		
	template< typename TNativeType >
	inline const bool StaticFieldHandle<TNativeType>::SetValue( JNIEnv* local_env, const TFieldType& value_storage ) const
	{
	
	};
};

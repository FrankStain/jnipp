// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const StaticField& other )
		: m_class_handle{ other.m_class_handle }
		, m_field_id{ other.m_field_id }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField<TNativeType>::StaticField( StaticField&& other )
		: m_class_handle{ std::move( other.m_class_handle ) }
		, m_field_id{ std::move( other.m_field_id ) }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const std::string& class_name, const std::string& field_name )
		: StaticField{ class_name.c_str(), field_name.c_str() }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const Class& class_handle, const std::string& field_name )
		: StaticField{ class_handle, field_name.c_str() }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const char* class_name, const char* field_name )
		: StaticField{ Class{ class_name }, field_name }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const Class& class_handle, const char* field_name )
		: StaticField{ class_handle, field_name, IGNORE_FAILURE }
	{
		JNI_ENSURES( m_field_id != 0 );
	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const std::string& class_name, const std::string& field_name, IgnoreFailure )
		: StaticField{ class_name.c_str(), field_name.c_str(), IGNORE_FAILURE }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const Class& class_handle, const std::string& field_name, IgnoreFailure )
		: StaticField{ class_handle, field_name.c_str(), IGNORE_FAILURE }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const char* class_name, const char* field_name, IgnoreFailure )
		: StaticField{ Class{ class_name }, field_name, IGNORE_FAILURE }
	{

	}

	template< typename TNativeType >
	StaticField<TNativeType>::StaticField( const Class& class_handle, const char* field_name, IgnoreFailure )
		: m_class_handle{ class_handle }
	{
		JNI_EXPECTS( m_class_handle.IsValid() );
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env	= VirtualMachine::GetLocalEnvironment();
		m_field_id		= local_env->GetStaticFieldID( *m_class_handle, field_name, Signature::GetString() );
	}

	template< typename TNativeType >
	inline const bool StaticField<TNativeType>::GetValue( TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), false, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return GetValue( local_env, value_storage );
	}

	template< typename TNativeType >
	inline TNativeType StaticField<TNativeType>::GetValue( const TNativeType& default_value ) const
	{
		TNativeType value;
		return ( GetValue( value ) )? value : default_value;
	}

	template< typename TNativeType >
	inline const bool StaticField<TNativeType>::GetValue( JNIEnv* local_env, TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !IsValid(), false, "Field handle was not initialized properly." );
		JNI_RETURN_IF_E( LOCAL_FRAME_SIZE && ( local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), false, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		auto value_source = (JavaType)(local_env->*FIELD_READ_HANDLER)( *m_class_handle, m_field_id );
		Marshaling::FromJava( value_source, value_storage );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, true );
		local_env->PopLocalFrame( nullptr );
		return true;
	}

	template< typename TNativeType >
	inline const bool StaticField<TNativeType>::SetValue( const TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), false, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return SetValue( local_env, value_storage );
	}

	template< typename TNativeType >
	inline const bool StaticField<TNativeType>::SetValue( JNIEnv* local_env, const TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !IsValid(), false, "Field handle was not initialized properly." );
		JNI_RETURN_IF_E( LOCAL_FRAME_SIZE && ( local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), false, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		JavaType value_destination;
		Marshaling::ToJava( value_storage, value_destination );
		(local_env->*FIELD_WRITE_HANDLER)( *m_class_handle, m_field_id, value_destination );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, true );
		local_env->PopLocalFrame( nullptr );
		return true;
	}

	template< typename TNativeType >
	inline const StaticField<TNativeType>& StaticField<TNativeType>::operator=( const StaticField& other )
	{
		m_class_handle	= other.m_class_handle;
		m_field_id		= other.m_field_id;
		return *this;
	}

	template< typename TNativeType >
	inline const StaticField<TNativeType>& StaticField<TNativeType>::operator=( StaticField&& other )
	{
		m_class_handle	= std::move( other.m_class_handle );
		m_field_id		= std::move( other.m_field_id );
		return *this;
	}
}

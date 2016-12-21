// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TNativeType >
	FieldHandle<TNativeType>::FieldHandle( const FieldHandle& other )
		: m_field_id( other.m_field_id )
	{

	};

	template< typename TNativeType >
	FieldHandle<TNativeType>::FieldHandle( FieldHandle&& other )
		: m_field_id( std::move( other.m_field_id ) )
	{

	};

	template< typename TNativeType >
	FieldHandle<TNativeType>::FieldHandle( const std::string& class_name, const std::string& field_name )
		: FieldHandle( class_name.c_str(), field_name.c_str() )
	{

	};

	template< typename TNativeType >
	FieldHandle<TNativeType>::FieldHandle( const Class& class_handle, const std::string& field_name )
		: FieldHandle( *class_handle, field_name.c_str() )
	{

	};

	template< typename TNativeType >
	FieldHandle<TNativeType>::FieldHandle( const char* class_name, const char* field_name )
		: FieldHandle( Class{ class_name }, field_name )
	{

	};

	template< typename TNativeType >
	FieldHandle<TNativeType>::FieldHandle( const Class& class_handle, const char* field_name )
		: FieldHandle( *class_handle, field_name )
	{

	};

	template< typename TNativeType >
	FieldHandle<TNativeType>::FieldHandle( jclass class_ref, const char* field_name )
	{
		JNI_EXPECTS( class_ref != nullptr );
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		auto local_env	= VirtualMachine::GetLocalEnvironment();
		m_field_id		= local_env->GetFieldID( class_ref, field_name, Signature::GetString() );

		JNI_ENSURES( m_field_id != 0 );
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::GetValue( const Object& object_handle, TNativeType& value_storage ) const
	{
		return GetValue( *object_handle, value_storage );
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::GetValue( jobject object_ref, TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), false, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return GetValue( local_env, object_ref, value_storage );
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::GetValue( JNIEnv* local_env, const Object& object_handle, TNativeType& value_storage ) const
	{
		return GetValue( local_env, *object_handle, value_storage );
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::GetValue( JNIEnv* local_env, jobject object_ref, TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !IsValid(), false, "Field handle was not initialized properly." );
		JNI_RETURN_IF_E( object_ref == nullptr, false, "Attempt to get the value of field from null object." );
		JNI_RETURN_IF_E( LOCAL_FRAME_SIZE && ( local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), false, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		auto value_source = (JavaType)(local_env->*FIELD_READ_HANDLER)( object_ref, m_field_id );
		Marshaling::FromJava( value_source, value_storage );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, true );
		local_env->PopLocalFrame( nullptr );
		return true;
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::SetValue( const Object& object_handle, const TNativeType& value_storage ) const
	{
		return SetValue( *object_handle, value_storage );
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::SetValue( jobject object_ref, const TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), false, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		auto local_env	= VirtualMachine::GetLocalEnvironment();

		return SetValue( local_env, object_ref, value_storage );
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::SetValue( JNIEnv* local_env, const Object& object_handle, const TNativeType& value_storage ) const
	{
		return SetValue( local_env, *object_handle, value_storage );
	};

	template< typename TNativeType >
	inline const bool FieldHandle<TNativeType>::SetValue( JNIEnv* local_env, jobject object_ref, const TNativeType& value_storage ) const
	{
		JNI_RETURN_IF_E( !IsValid(), false, "Field handle was not initialized properly." );
		JNI_RETURN_IF_E( object_ref == nullptr, false, "Attempt to set the value of field to null object." );
		JNI_RETURN_IF_E( LOCAL_FRAME_SIZE && ( local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), false, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		JavaType value_destination;
		Marshaling::ToJava( value_storage, value_destination );
		(local_env->*FIELD_WRITE_HANDLER)( object_ref, m_field_id, value_destination );

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, true );
		local_env->PopLocalFrame( nullptr );
		return true;
	};
};

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	/// @brief	Handle to field of Java object.
	template< typename TNativeType >
	class FieldHandle final
	{
		friend class JniEnv;
	public:
		FieldHandle() = delete;
		FieldHandle( const FieldHandle& other );
		FieldHandle( FieldHandle&& other );
		FieldHandle( const std::string& class_name, const std::string& field_name );
		FieldHandle( const ClassHandle& class_handle, const std::string& field_name );
		FieldHandle( const char* class_name, const char* field_name );
		FieldHandle( const ClassHandle& class_handle, const char* field_name );

		
		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_field_id != 0; };

		/// @brief	Get the value of field from given handle to object.
		inline const bool GetValue( const ObjectHandle& object_handle, TFieldType& value_storage ) const;
		
		/// @brief	Get the value of field from given object ref.
		inline const bool GetValue( jobject object_ref, TFieldType& value_storage ) const;

		
		/// @brief	Set the value of field to given object by its handle.
		inline const bool SetValue( const ObjectHandle& object_handle, const TFieldType& value_storage ) const;
		
		/// @brief	Set the value of field to given object by its ref.
		inline const bool SetValue( jobject object_ref, const TFieldType& value_storage ) const;

		
		inline explicit operator const bool () const	{ return IsValid(); };

	private:
		using JavaType	= typename marshaling::JniEnvFacade<TNativeType>::JavaType;
		using Signature	= typename marshaling::JniEnvFacade<TNativeType>::Signature;

		FieldHandle( jclass class_ref, const char* field_name );

		
		/// @brief	Get the value of field from given handle to object.
		inline const bool GetValue( JNIEnv* local_env, const ObjectHandle& object_handle, TFieldType& value_storage ) const;
		
		/// @brief	Get the value of field from given object ref.
		inline const bool GetValue( JNIEnv* local_env, jobject object_ref, TFieldType& value_storage ) const;

		
		/// @brief	Set the value of field to given object by its handle.
		inline const bool SetValue( JNIEnv* local_env, const ObjectHandle& object_handle, const TFieldType& value_storage ) const;
		
		/// @brief	Set the value of field to given object by its ref.
		inline const bool SetValue( JNIEnv* local_env, jobject object_ref, const TFieldType& value_storage ) const;

	private:
		constexpr static size_t LOCAL_FRAME_SIZE	= marshaling::JniEnvFacade<TNativeType>::LOCAL_FRAME_SIZE;
		constexpr static auto FIELD_READ_HANDLER	= marshaling::JniEnvFacade<TNativeType>::FIELD_READ_HANDLER;
		constexpr static auto FIELD_WRITE_HANDLER	= marshaling::JniEnvFacade<TNativeType>::FIELD_WRITE_HANDLER;

		jfieldID	m_field_id	= 0;	// Field id for JNI.
	};
};

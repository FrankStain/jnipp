// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/// @brief	Handle to field of Java object.
	template< typename TNativeType >
	class FieldHandle final
	{
		friend class JniEnv;
	public:
		FieldHandle() = default;
		FieldHandle( const FieldHandle& other );
		FieldHandle( FieldHandle&& other );
		FieldHandle( const std::string& class_name, const std::string& field_name );
		FieldHandle( const Class& class_handle, const std::string& field_name );
		FieldHandle( const char* class_name, const char* field_name );
		FieldHandle( const Class& class_handle, const char* field_name );


		/// @brief	Get the value of field from given handle to object.
		inline const bool GetValue( const ObjectHandle& object_handle, TNativeType& value_storage ) const;
		
		/// @brief	Get the value of field from given object ref.
		inline const bool GetValue( jobject object_ref, TNativeType& value_storage ) const;

		
		/// @brief	Set the value of field to given object by its handle.
		inline const bool SetValue( const ObjectHandle& object_handle, const TNativeType& value_storage ) const;
		
		/// @brief	Set the value of field to given object by its ref.
		inline const bool SetValue( jobject object_ref, const TNativeType& value_storage ) const;


		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const									{ return m_field_id != 0; };

		/// @brief	Get the JNI id of Java member field.
		inline jfieldID GetFieldId() const									{ return m_field_id; };


		inline const FieldHandle& operator = ( const FieldHandle& other )	{ m_field_id = other.m_field_id; return *this; };
		inline const FieldHandle& operator = ( FieldHandle&& other )		{ m_field_id = std::move( other.m_field_id ); return *this; };

		
		inline explicit operator const bool () const						{ return IsValid(); };
		inline jfieldID operator * () const									{ return GetFieldId(); };

	private:
		using JavaType	= typename Marshaling::JniEnvFacade<TNativeType>::JavaType;
		using Signature	= typename Marshaling::JniEnvFacade<TNativeType>::Signature;

		FieldHandle( jclass class_ref, const char* field_name );

		
		/// @brief	Get the value of field from given handle to object.
		inline const bool GetValue( JNIEnv* local_env, const ObjectHandle& object_handle, TNativeType& value_storage ) const;
		
		/// @brief	Get the value of field from given object ref.
		inline const bool GetValue( JNIEnv* local_env, jobject object_ref, TNativeType& value_storage ) const;

		
		/// @brief	Set the value of field to given object by its handle.
		inline const bool SetValue( JNIEnv* local_env, const ObjectHandle& object_handle, const TNativeType& value_storage ) const;
		
		/// @brief	Set the value of field to given object by its ref.
		inline const bool SetValue( JNIEnv* local_env, jobject object_ref, const TNativeType& value_storage ) const;

	private:
		constexpr static size_t LOCAL_FRAME_SIZE	= Marshaling::JniEnvFacade<TNativeType>::LOCAL_FRAME_SIZE;
		constexpr static auto FIELD_READ_HANDLER	= Marshaling::JniEnvFacade<TNativeType>::FIELD_READ_HANDLER;
		constexpr static auto FIELD_WRITE_HANDLER	= Marshaling::JniEnvFacade<TNativeType>::FIELD_WRITE_HANDLER;

		jfieldID	m_field_id	= nullptr;	// Field id for JNI.
	};
};

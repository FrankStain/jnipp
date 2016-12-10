// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	/// @brief	Handle to static field of Java class.
	template< typename TNativeType >
	class StaticFieldHandle final
	{
		friend class JniEnv;
	public:
		StaticFieldHandle() = default;
		StaticFieldHandle( const StaticFieldHandle& other );
		StaticFieldHandle( StaticFieldHandle&& other );
		StaticFieldHandle( const std::string& class_name, const std::string& field_name );
		StaticFieldHandle( const ClassHandle& class_handle, const std::string& field_name );
		StaticFieldHandle( const char* class_name, const char* field_name );
		StaticFieldHandle( const ClassHandle& class_handle, const char* field_name );


		/// @brief	Get the value of field.
		inline const bool GetValue( TNativeType& value_storage ) const;

		/// @brief	Set the value of field.
		inline const bool SetValue( const TNativeType& value_storage ) const;

		
		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_class_handle.IsValid() && ( m_field_id != 0 ); };

		/// @brief	Get the JNI id of Java static field.
		inline jfieldID GetFieldId() const				{ return m_field_id; };


		inline const StaticFieldHandle& operator = ( const StaticFieldHandle& other );
		inline const StaticFieldHandle& operator = ( StaticFieldHandle&& other );


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jfieldID operator * () const				{ return GetFieldId(); };

	private:
		using JavaType	= typename marshaling::JniEnvFacade<TNativeType>::JavaType;
		using Signature	= typename marshaling::JniEnvFacade<TNativeType>::Signature;

		/// @brief	Get the value of field.
		inline const bool GetValue( JNIEnv* local_env, TNativeType& value_storage ) const;

		/// @brief	Set the value of field.
		inline const bool SetValue( JNIEnv* local_env, const TNativeType& value_storage ) const;

	private:
		constexpr static size_t LOCAL_FRAME_SIZE	= marshaling::JniEnvFacade<TNativeType>::LOCAL_FRAME_SIZE;
		constexpr static auto FIELD_READ_HANDLER	= marshaling::JniEnvFacade<TNativeType>::STATIC_FIELD_READ_HANDLER;
		constexpr static auto FIELD_WRITE_HANDLER	= marshaling::JniEnvFacade<TNativeType>::STATIC_FIELD_WRITE_HANDLER;

		ClassHandle	m_class_handle;		// Handle to class of field.
		jfieldID	m_field_id	= 0;	// Field id for JNI.
	};
};

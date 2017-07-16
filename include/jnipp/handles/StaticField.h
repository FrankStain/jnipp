// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/// @brief	Handle of arbitrary Java static field.
	template< typename TNativeType >
	class StaticField final
	{
		friend class Environment;
	public:
		StaticField() = default;
		StaticField( const StaticField& other );
		StaticField( StaticField&& other );
		StaticField( const std::string& class_name, const std::string& field_name );
		StaticField( const Class& class_handle, const std::string& field_name );
		StaticField( const char* class_name, const char* field_name );
		StaticField( const Class& class_handle, const char* field_name );


		/// @brief	Get the value of field.
		inline const bool GetValue( TNativeType& value_storage ) const;

		/// @brief	Set the value of field.
		inline const bool SetValue( const TNativeType& value_storage ) const;


		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_class_handle.IsValid() && ( m_field_id != 0 ); };

		/// @brief	Get the JNI id of Java static field.
		inline jfieldID GetFieldId() const				{ return m_field_id; };


		inline const StaticField& operator = ( const StaticField& other );
		inline const StaticField& operator = ( StaticField&& other );


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jfieldID operator * () const				{ return GetFieldId(); };

	private:
		using JavaType	= typename Marshaling::JavaType<TNativeType>;
		using Signature	= typename Marshaling::TypeSignature<TNativeType>;

		/// @brief	Get the value of field.
		inline const bool GetValue( JNIEnv* local_env, TNativeType& value_storage ) const;

		/// @brief	Set the value of field.
		inline const bool SetValue( JNIEnv* local_env, const TNativeType& value_storage ) const;

	private:
		constexpr static size_t LOCAL_FRAME_SIZE	= Marshaling::NativeTypeTraits<TNativeType>::LOCAL_FRAME_SIZE;
		constexpr static auto FIELD_READ_HANDLER	= Marshaling::NativeTypeTraits<TNativeType>::STATIC_FIELD_READ_HANDLER;
		constexpr static auto FIELD_WRITE_HANDLER	= Marshaling::NativeTypeTraits<TNativeType>::STATIC_FIELD_WRITE_HANDLER;

		Class		m_class_handle;				// Handle to class of field.
		jfieldID	m_field_id		= nullptr;	// Field id for JNI.
	};
};

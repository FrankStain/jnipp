// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	/// @brief	Java class handle through JNI interface.
	class ClassHandle final
	{
		friend class ObjectHandle;	// Grant access to `AcquireHandle` function.
	public:
		ClassHandle() = default;
		ClassHandle( const ClassHandle& other );
		ClassHandle( ClassHandle&& other );
		ClassHandle( const std::string& class_name );
		ClassHandle( const char* class_name );


		/// @brief	Invalidate the handle.
		void Invalidate();

		/// @brief	Returns the canonical name of this class or empty string for invalid class.
		const std::string GetCanonicalName() const;

		/// @brief	Get the name of this class or empty string for invalid class.
		const std::string GetName() const;

		/// @brief	Returns the simple name of this class or empty string for invalid class.
		const std::string GetSimpleName() const;

		/// @brief	Get the handle to parent class, if available.
		ClassHandle GetParentClassHandle() const;

		/// @brief	Check the class handle carries valid value.
		inline const bool IsValid() const		{ return m_class_ref != nullptr; };

		/// @brief	Get the JNI representation of Java class reference.
		inline jclass GetJniReference() const	{ return m_class_ref.get(); };


		const ClassHandle& operator = ( jclass class_ref );
		const ClassHandle& operator = ( const ClassHandle& other );
		const ClassHandle& operator = ( ClassHandle&& other );
		const ClassHandle& operator = ( const std::string& class_name );
		const ClassHandle& operator = ( const char* class_name );

		
		inline explicit operator const bool () const	{ return IsValid(); };
		inline jclass operator * () const				{ return GetJniReference(); };

	private:
		/// @brief	Acquire the handle of class via it's name.
		void AcquireHandle( const char* class_name );

		/// @brief	Acquire the handle of class via handle of object.
		void AcquireHandle( jobject object_ref );

	private:
		std::shared_ptr<_jclass>	m_class_ref;	// Shared JNI representation of Java class global reference.
	};
};

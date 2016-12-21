// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/// @brief	Handle of arbitrary Java object.
	class Object
	{
	public:
		/// @brief	Constructs new object of given class and using given construction arguments.
		template< typename... TNativeArguments >
		static Object NewObject( const Class& class_handle, const TNativeArguments&... arguments );

		Object() = default;
		Object( jobject object_ref );
		Object( const Class& class_handle );
		Object( Class&& class_handle );
		Object( const Object& other );
		Object( Object&& other );


		/// @brief	Invalidate the handle.
		void Invalidate();

		/// @brief	Check the object handle carries valid value.
		inline const bool IsValid() const					{ return m_object_ref != nullptr; };

		/// @brief	Get the handle to class of stored object.
		inline const Class& GetClass() const				{ RetrieveClass(); return m_class_handle; };

		/// @brief	Get the JNI representation of Java object reference.
		inline jobject GetJniReference() const				{ return m_object_ref.get(); };


		const Object& operator = ( jobject object_ref );
		const Object& operator = ( const Class& class_handle );
		const Object& operator = ( Class&& class_handle );
		const Object& operator = ( const Object& other );
		const Object& operator = ( Object&& other );


		inline explicit operator const bool () const		{ return IsValid(); };
		inline jobject operator * () const					{ return GetJniReference(); };

	private:
		/// @brief	Delete global ref to object.
		static void DeleteObjectRef( jobject object_ref );


		/// @brief	Lazy initialization of `m_class_handle`.
		void RetrieveClass() const;

		/// @brief	Acquire the global ref to object.
		void AcquireObjectRef( jobject object_ref );

	private:
		std::shared_ptr<_jobject>	m_object_ref;	// Shared JNI representation of Java object global reference.
		mutable Class				m_class_handle;	// Handle to class of stored object.
	};
};

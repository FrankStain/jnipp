// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	/// @brief	Java object handle through JNI interface.
	class ObjectHandle final
	{
	public:
		ObjectHandle() = default;
		ObjectHandle( jobject object_ref );
		ObjectHandle( const ClassHandle& class_handle );
		ObjectHandle( ClassHandle&& class_handle );
		ObjectHandle( const ObjectHandle& other );
		ObjectHandle( ObjectHandle&& other );


		/// @brief	Invalidate the handle.
		void Invalidate();

		/// @brief	Check the object handle carries valid value.
		inline const bool IsValid() const					{ return m_object != nullptr; };

		/// @brief	Get the handle to class of stored object.
		inline const ClassHandle& GetClassHandle() const	{ InitClassHandle(); return m_class_handle; };


		const ObjectHandle& operator = ( jobject object_ref );
		const ObjectHandle& operator = ( const ClassHandle& class_handle );
		const ObjectHandle& operator = ( ClassHandle&& class_handle );
		const ObjectHandle& operator = ( const ObjectHandle& other );
		const ObjectHandle& operator = ( ObjectHandle&& other );


		inline explicit operator const bool () const		{ return IsValid(); };
		inline jobject operator * () const					{ return m_object.get(); };

	private:
		/// @brief	Delete global ref to object.
		static void DeleteObjectRef( jobject object_ref );


		/// @brief	Lazy initialization of `m_class_handle`.
		void InitClassHandle() const;

		/// @brief	Acquire the global ref to object.
		void AcquireObjectRef( jobject object_ref );

	private:
		std::shared_ptr<_jobject>	m_object;		// Global ref to stored object.
		mutable ClassHandle			m_class_handle;	// Handle to class of stored object.
	};
};

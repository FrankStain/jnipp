// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/**
		@brief	Special accessor to table of JNI handles for some class, stored in `Jni::VirtualMachine`.
		`Jni::VirtualMachine` can store some already constructed handles. It may keep your time when constructing a lot of object instances.
		Or, it may keep your time when the instance of such JNI object frequently constructed and has small lifetime.
		Your handles for such object may be stored inside of some 'table' (`struct` for ex.) and you may get access to it via instance of `CachedHandles` template.

		@note	The tables of JNI handles always stored by `Jni::VirtualMachine`. So it have to be ready before the c-tor of `Jni::CachedHandles`.

		@tparam	TCachedHandles	Type of the cached table.
		@tparam	IS_PERMANENT	Indicates that the cached table must be allocated all the time the `Jni::VirtualMachine` initialized.
	*/
	template< typename TCachedHandles, bool IS_PERMANENT = false >
	class CachedHandles final
	{
	// Construction and assignation.
	public:
		CachedHandles();
		CachedHandles( const CachedHandles& other );
		CachedHandles( CachedHandles&& other );
		~CachedHandles();

		// There is nothing different between two instances of same type.
		inline CachedHandles& operator = ( const CachedHandles& other ) = delete;
		inline CachedHandles& operator = ( CachedHandles&& other ) = delete;

	// public interface.
	public:
		/// @brief	Get the cached handles.
		inline const TCachedHandles& GetHandles() const		{ return *m_storage.GetHandles(); };

		inline const TCachedHandles* operator -> () const	{ return m_storage.GetHandles(); };

	// Private state.
	private:
		Utils::HandlesStorageEntry<TCachedHandles>&	m_storage;
	};
}

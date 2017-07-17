// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::CachedHandles( const CachedHandles& other )
		: m_storage( other.m_storage )
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		RetainStorage();
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::CachedHandles( CachedHandles&& other )
		: m_storage( other.m_storage )
	{
		other.m_storage = nullptr;
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::CachedHandles( const CachedHandles<TCachedHandles, !IS_PERMANENT>& other )
		: m_storage( other.m_storage )
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		RetainStorage();

		JNI_RETURN_IF( !IS_PERMANENT || !m_storage );
		m_storage->SetPermanent();
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::CachedHandles( CachedHandles<TCachedHandles, !IS_PERMANENT>&& other )
		: m_storage( other.m_storage )
	{
		other.m_storage = nullptr;

		JNI_RETURN_IF( !IS_PERMANENT || !m_storage );
		m_storage->SetPermanent();
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::~CachedHandles()
	{
		JNI_RETURN_IF( m_storage == nullptr );
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		m_storage->Release();
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	inline Utils::HandlesStorageEntry<TCachedHandles>& CachedHandles<TCachedHandles, IS_PERMANENT>::GetStorage() const
	{
		JNI_RETURN_IF( m_storage != nullptr, *m_storage );
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		m_storage = VirtualMachine::GetHandlesStorage<TCachedHandles>();
		m_storage->Retain();

		if( IS_PERMANENT )
		{
			m_storage->SetPermanent();
		}

		return *m_storage;
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	inline CachedHandles<TCachedHandles, IS_PERMANENT>& CachedHandles<TCachedHandles, IS_PERMANENT>::operator=( const CachedHandles& other )
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };

		ReleaseStorage();
		m_storage = other.m_storage;
		RetainStorage();

		return *this;
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	inline CachedHandles<TCachedHandles, IS_PERMANENT>& CachedHandles<TCachedHandles, IS_PERMANENT>::operator=( CachedHandles&& other )
	{
		if( m_storage != nullptr )
		{
			Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
			ReleaseStorage();
		}

		m_storage		= other.m_storage;
		other.m_storage	= nullptr;

		return *this;
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	inline CachedHandles<TCachedHandles, IS_PERMANENT>& CachedHandles<TCachedHandles, IS_PERMANENT>::operator=(
		const CachedHandles<TCachedHandles, !IS_PERMANENT>& other
	)
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };

		ReleaseStorage();
		m_storage = other.m_storage;
		RetainStorage();

		if( IS_PERMANENT && ( m_storage != nullptr ) )
		{
			m_storage->SetPermanent();
		}

		return *this;
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	inline CachedHandles<TCachedHandles, IS_PERMANENT>& CachedHandles<TCachedHandles, IS_PERMANENT>::operator=(
		CachedHandles<TCachedHandles, !IS_PERMANENT>&& other
	)
	{
		if( m_storage != nullptr )
		{
			Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
			ReleaseStorage();
		}

		m_storage		= other.m_storage;
		other.m_storage	= nullptr;

		if( IS_PERMANENT && ( m_storage != nullptr ) )
		{
			m_storage->SetPermanent();
		}

		return *this;
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	inline void CachedHandles<TCachedHandles, IS_PERMANENT>::RetainStorage() const
	{
		JNI_RETURN_IF( m_storage == nullptr );
		m_storage->Retain();
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	inline void CachedHandles<TCachedHandles, IS_PERMANENT>::ReleaseStorage() const
	{
		JNI_RETURN_IF( m_storage == nullptr );
		m_storage->Release();
	}
}

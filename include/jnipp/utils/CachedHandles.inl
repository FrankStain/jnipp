// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::CachedHandles()
		: m_storage( VirtualMachine::GetHandlesStorage<TCachedHandles>() )
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		m_storage.Retain();

		if( IS_PERMANENT )
		{
			m_storage.SetPermanent();
		}
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::CachedHandles( const CachedHandles& other )
		: m_storage( other.m_storage )
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		m_storage.Retain();
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::CachedHandles( CachedHandles&& other )
		: m_storage( other.m_storage )
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		m_storage.Retain();
	}

	template< typename TCachedHandles, bool IS_PERMANENT >
	CachedHandles<TCachedHandles, IS_PERMANENT>::~CachedHandles()
	{
		Utils::MutexLock lock{ VirtualMachine::GetCacheMutex() };
		m_storage.Release();
	}
}

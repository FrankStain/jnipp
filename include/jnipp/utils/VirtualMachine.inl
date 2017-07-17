// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TCachedHandles >
	inline Utils::HandlesStorageEntry<TCachedHandles>& VirtualMachine::GetHandlesStorage()
	{
		Utils::MutexLock lock{ GetInstance().m_cache_mutex };

		std::unique_ptr<Utils::HandlesCacheEntry>& handles_storage = GetInstance().m_handles_cache[ { typeid( TCachedHandles ) } ];
		JNI_RETURN_IF( handles_storage, *static_cast<Utils::HandlesStorageEntry<TCachedHandles>*>( handles_storage.get() ) );

		auto new_storage = new Utils::HandlesStorageEntry<TCachedHandles>{};
		handles_storage.reset( new_storage );
		return *new_storage;
	}
}

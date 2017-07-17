// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	/// @brief	Regular entry of handles cache for `Jni::VirtualMachine`.
	class HandlesCacheEntry
	{
	//
	public:
		virtual ~HandlesCacheEntry() = default;

	protected:
		HandlesCacheEntry() = default;
		HandlesCacheEntry( const HandlesCacheEntry& ) = delete;
		HandlesCacheEntry( HandlesCacheEntry&& ) = delete;
	};


	/// @brief	Handles cache entity, that store some handles table.
	template< typename TCachedHandles >
	class HandlesStorageEntry final : public HandlesCacheEntry
	{
	public:
		virtual ~HandlesStorageEntry()				{ if( m_handles != nullptr ){ DestructHandles(); } };


		/// @brief	Get the allocated handles or `nullptr` if ones not allocated.
		inline TCachedHandles* GetHandles() const	{ return m_handles; };

		/// @brief	Set this storage permanent.
		inline void SetPermanent()					{ m_is_permanent = true; };


		/// @brief	Retain the handles.
		inline void Retain()
		{
			if( ( m_reference_counter == 0 ) && ( m_handles == nullptr ) )
			{
				ConstructHandles();
			}

			++m_reference_counter;
		}

		/// @brief	Release the handles.
		inline void Release()
		{
			JNI_EXPECTS( m_reference_counter > 0 );

			--m_reference_counter;
			JNI_RETURN_IF( ( m_reference_counter > 0 ) || m_is_permanent );

			DestructHandles();
			m_handles = nullptr;
		}

	public:
		inline void ConstructHandles()	{ m_handles = new( m_memory ) TCachedHandles(); };
		inline void DestructHandles()	{ m_handles->~TCachedHandles(); };

	private:
		bool			m_is_permanent		= false;			// Permanentness flag.
		int32_t			m_reference_counter	= 0;				// Reference counter.
		TCachedHandles*	m_handles			= nullptr;			// Pointer to constructed handles.
		uint8_t			m_memory[ sizeof( TCachedHandles ) ];	// Memory for stored handles.
	};
}
}

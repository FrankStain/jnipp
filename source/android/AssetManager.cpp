#include <jnipp/jnipp.h>
#include <jnipp/android/AssetManager.h>
#include <android/asset_manager_jni.h>

namespace
{
	class ScopedAsset final
	{
	public:
		inline ScopedAsset( AAsset* asset ) : m_asset{ asset } {};
		inline ~ScopedAsset() { if( m_asset ){ AAsset_close( m_asset ); } };


		inline AAsset* Get() const	{ return m_asset; };

	private:
		AAsset*	m_asset = nullptr;
	};

	class ScopedAssetFolder final
	{
	public:
		inline ScopedAssetFolder( AAssetDir* asset_dir ) : m_asset_dir{ asset_dir } {};
		inline ~ScopedAssetFolder() { if( m_asset_dir ){ AAssetDir_close( m_asset_dir ); } };

		inline AAssetDir* Get() const	{ return m_asset_dir; };

	private:
		AAssetDir*	m_asset_dir = nullptr;
	};
}


namespace Jni
{
namespace Android
{
	void AssetManager::AcquireAssets()
	{
		m_assets = nullptr;
		JNI_RETURN_IF( !IsValid() );
		JNI_EXPECTS( IsInstanceOf( m_handles->jni_class ) );

		auto local_env	= VirtualMachine::GetLocalEnvironment();
		m_assets		= AAssetManager_fromJava( local_env, GetJniReference() );
		JNI_ENSURES( m_assets != nullptr );
	}

	const bool AssetManager::IsValidFolder( const std::string& path ) const
	{
		ScopedAssetFolder folder{ AAssetManager_openDir( m_assets, path.c_str() ) };
		return AAssetDir_getNextFileName( folder.Get() ) != nullptr;
	}

	const bool AssetManager::IsValidFile( const std::string& path ) const
	{
		ScopedAsset asset{ AAssetManager_open( m_assets, path.c_str(), static_cast<int32_t>( AssetOpenMode::Default ) ) };
		return asset.Get() != nullptr;
	}

	std::shared_ptr<AAsset> AssetManager::OpenAsset( const std::string& path, const AssetOpenMode open_mode ) const
	{
		return {
			AAssetManager_open( m_assets, path.c_str(), static_cast<int32_t>( open_mode ) ),
			[]( AAsset* asset ) { AAsset_close( asset ); }
		};
	}

	void AssetManager::ListFolder( std::deque<std::string>* files, std::deque<std::string>* folders, const std::string& path ) const
	{
		JNI_RETURN_IF( !files && !folders );
		auto found_entities = m_handles->list_path.Call( *this, path );

		for( auto& entity : found_entities )
		{
			const std::string entity_path{ path + '/' + entity };
			if( IsValidFile( entity_path ) )
			{
				JNI_CONTINUE_IF( files == nullptr );
				files->push_back( std::move( entity ) );
			}
			else
			{
				JNI_CONTINUE_IF( folders == nullptr );
				folders->push_back( std::move( entity ) );
			}
		}
	}
}
}

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>
#include <android/asset_manager.h>
#include "AssetManager.const.h"


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.content.res.AssetManager` object.
	class AssetManager : Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'c', 'o', 'n', 't', 'e', 'n', 't', '/',
			'r', 'e', 's', '/',
			'A', 's', 's', 'e', 't', 'M', 'a', 'n', 'a', 'g', 'e', 'r'
		>;


		AssetManager() = default;
		AssetManager( jobject object_ref ) : Object( object_ref ) { AcquireAssets(); };
		AssetManager( const AssetManager& other ) : Object( other ) { AcquireAssets(); };
		AssetManager( AssetManager&& other ) : Object( other ) { AcquireAssets(); };


		/// @breif	Check that the given path leads to valid assets folder.
		const bool IsValidFolder( const std::string& path ) const;

		/// @brief	Check that the given path leads to valid asset file.
		const bool IsValidFile( const std::string& path ) const;

		/// @brief	Open the asset.
		std::shared_ptr<AAsset> OpenAsset( const std::string& path, const AssetOpenMode open_mode ) const;

		/// @brief	Query the asset manager to get all files in given folder.
		void ListFolder( std::deque<std::string>* files, std::deque<std::string>* folders, const std::string& path ) const;


		const AssetManager& operator = ( jobject object_ref )			{ Object::operator=( object_ref ); AcquireAssets(); return *this; };
		const AssetManager& operator = ( const AssetManager& other )	{ Object::operator=( other ); AcquireAssets(); return *this; };
		const AssetManager& operator = ( AssetManager&& other )			{ Object::operator=( other ); AcquireAssets(); return *this; };

	private:
		void AcquireAssets();

	private:
		struct AssetManagerHandles
		{
			Class	jni_class	= { ClassPath::GetString() };

			MemberFunction<std::vector<std::string>, std::string>	list_path	= { jni_class,	"list" };
		};

		AAssetManager*						m_assets	= nullptr;	// Low-level representation of assets manager.
		CachedHandles<AssetManagerHandles>	m_handles;				// Temporally cached and shared handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::AssetManager` type.
	template<>
	struct NativeTypeTraits<Jni::Android::AssetManager> : ObjectTypeTraits<Jni::Android::AssetManager> {};
}
}

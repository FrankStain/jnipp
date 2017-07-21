#include <jnipp/jnipp.h>
#include <jnipp/android/AssetManager.h>
#include <android/asset_manager_jni.h>


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
}
}

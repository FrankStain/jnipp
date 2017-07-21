// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Android
{
	/// @brief	Available asset opening modes.
	enum class AssetOpenMode : int32_t
	{
		Default			= AASSET_MODE_UNKNOWN,		// No specific information about how data will be accessed.
		RandomAccess	= AASSET_MODE_RANDOM,		// Read chunks, and seek forward and backward.
		ByteStreaming	= AASSET_MODE_STREAMING,	// Read sequentially, with an occasional forward seek.
		FlatMaping		= AASSET_MODE_BUFFER,		// Caller plans to ask for a read-only buffer with all data.
	};
}
}

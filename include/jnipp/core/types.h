// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/// @brief	Marker type to mark that the operation variant will ignore internal errors.
	struct IgnoreFailure {};


	/// @brief	Marking object, which may be used to indicate that the operation have to ignore internal errors.
	static constexpr IgnoreFailure IGNORE_FAILURE = {};
}

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	/// @brief	Check that the class `TBitfieldType` has member-field named `bits`.
	template< typename TBitfieldType, typename = int >
	struct HasBitsField : std::false_type {};

	/// @brief	Check that the class `TBitfieldType` has member-field named `bits`.
	template< typename TBitfieldType >
	struct HasBitsField<TBitfieldType, decltype( (void)TBitfieldType::bits, 0 )> : std::true_type {};
}
}

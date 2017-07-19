// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Type translation traits specification for bit-field types.
	template< class TBitfieldType, bool HAS_BITS = Utils::HasBitsField<TBitfieldType>::value >
	struct BitfieldTypeTraits;

	/// @brief	Type translation traits specification for bit-field types.
	template< class TBitfieldType >
	struct BitfieldTypeTraits<TBitfieldType, true> : NativeTypeTraits<decltype( std::declval<TBitfieldType>().bits )>
	{
		/// @brief	Underlying type for bit-field type.
		using UnderlyingType	= decltype( std::declval<TBitfieldType>().bits );

		/// @brief	Native type traits for underlying type of enumeration type.
		using UnderlyingTraits	= NativeTypeTraits<UnderlyingType>;


		/// @brief	C++ native type.
		using NativeType	= TBitfieldType;

		/// @brief	JNI representation of Java type.
		using JavaType		= typename UnderlyingTraits::JavaType;


		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination )
		{
			UnderlyingTraits::FromJava( source, destination.bits );
		}

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination )
		{
			UnderlyingTraits::FromJava( source.bits, destination );
		}
	};
}
}

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Type translation traits specification for enumeration types.
	template< typename TEnumType, bool IS_ENUM = std::is_enum<TEnumType>::value >
	struct EnumTypeTraits;

	/// @brief	Type translation traits specification for enumeration types.
	template< typename TEnumType >
	struct EnumTypeTraits<TEnumType, true> : NativeTypeTraits<typename std::underlying_type<TEnumType>::type>
	{
		/// @brief	Underlying type for enumeration type.
		using UnderlyingType	= typename std::underlying_type<TEnumType>::type;

		/// @brief	Native type traits for underlying type of enumeration type.
		using UnderlyingTraits	= NativeTypeTraits<UnderlyingType>;


		/// @brief	C++ native type.
		using NativeType	= TEnumType;

		/// @brief	JNI representation of Java type.
		using JavaType		= typename UnderlyingTraits::JavaType;


		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination )
		{
			UnderlyingType buffer;
			UnderlyingTraits::FromJava( source, buffer );
			destination = static_cast<TEnumType>( buffer );
		}

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination )
		{
			const UnderlyingType buffer = static_cast<UnderlyingType>( source );
			UnderlyingTraits::FromJava( buffer, destination );
		}
	};
}
}

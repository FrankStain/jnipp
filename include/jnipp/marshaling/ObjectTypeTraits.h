// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Type translation traits specification for object types.
	template< class TObjectType, bool IS_OBJECT_HANDLE = std::is_base_of<Object, TObjectType>::value >
	struct ObjectTypeTraits;

	/// @brief	Type translation traits specification for object types.
	template< class TObjectType >
	struct ObjectTypeTraits<TObjectType, true> : EnvironmentTraits<jobject>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	Java type signature.
		using Signature		= CombinedStaticString< StaticString<'L'>, typename TObjectType::ClassPath, StaticString<';'> >;

		/// @brief	C++ native type.
		using NativeType	= TObjectType;

		/// @brief	JNI representation of Java type.
		using JavaType		= jobject;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination )
		{
			destination = source;
		}

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination )
		{
			destination = *source;
		}
	};
}
}

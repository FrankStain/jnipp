// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Class` type.
	template<>
	struct NativeTypeTraits<Jni::Class> : EnvironmentTraits<jobject>, JavaTypeTraits<jclass>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	C++ native type.
		using NativeType	= Jni::Class;

		/// @brief	JNI representation of Java type.
		using JavaType		= jclass;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination )
		{
			destination = source;
		};

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination )
		{
			destination = *source;
		};
	};
};
};

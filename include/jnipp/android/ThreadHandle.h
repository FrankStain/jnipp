// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace Jni
{
namespace Android
{
	/// @brief	Handle to `java.lang.Thread` object.
	class Thread : public Object
	{
	public:
		Thread() = default;
		Thread( jobject object_ref ) : Object( object_ref ) {};
		Thread( const Thread& other ) : Object( other ) {};
		Thread( Thread&& other ) : Object( other ) {};

		const Thread& operator = ( jobject object_ref )		{ Object::operator=( object_ref ); return *this; };
		const Thread& operator = ( const Thread& other )	{ Object::operator=( other ); return *this; };
		const Thread& operator = ( Thread&& other )			{ Object::operator=( other ); return *this; };
	};
};

namespace Marshaling
{
	/// @brief	Traits specification for native `std::u16string` type.
	template<>
	struct TypeTraits<Jni::Android::Thread> : EnvironmentTraits<jobject>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	Java type signature.
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'T', 'h', 'r', 'e', 'a', 'd'>;

		/// @brief	C++ native type.
		using NativeType	= Jni::Android::Thread;

		/// @brief	JNI representation of Java type.
		using JavaType		= jobject;

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

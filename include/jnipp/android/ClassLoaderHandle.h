// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `java.lang.ClassLoader` object.
	class ClassLoader : public Object
	{
	public:
		ClassLoader() = default;
		ClassLoader( jobject object_ref ) : Object( object_ref ) {};
		ClassLoader( const ClassLoader& other ) : Object( other ) {};
		ClassLoader( ClassLoader&& other ) : Object( other ) {};

		const ClassLoader& operator = ( jobject object_ref )			{ Object::operator=( object_ref ); return *this; };
		const ClassLoader& operator = ( const ClassLoader& other )		{ Object::operator=( other ); return *this; };
		const ClassLoader& operator = ( ClassLoader&& other )			{ Object::operator=( other ); return *this; };
	};
};

namespace Marshaling
{
	/// @brief	Traits specification for native `std::u16string` type.
	template<>
	struct TypeTraits<Jni::Android::ClassLoader> : EnvironmentTraits<jobject>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	Java type signature.
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's', 'L', 'o', 'a', 'd', 'e', 'r'>;

		/// @brief	C++ native type.
		using NativeType	= Jni::Android::ClassLoader;

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

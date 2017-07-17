// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.view.MotionEvent` object.
	class MotionEvent : public Object
	{
	public:
		MotionEvent() = default;
		MotionEvent( jobject object_ref ) : Object( object_ref ) {};
		MotionEvent( const MotionEvent& other ) : Object( other ) {};
		MotionEvent( MotionEvent&& other ) : Object( other ) {};

		const MotionEvent& operator = ( jobject object_ref )		{ Object::operator=( object_ref ); return *this; };
		const MotionEvent& operator = ( const MotionEvent& other )	{ Object::operator=( other ); return *this; };
		const MotionEvent& operator = ( MotionEvent&& other )		{ Object::operator=( other ); return *this; };
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::MotionEvent` type.
	template<>
	struct NativeTypeTraits<Jni::Android::MotionEvent> : EnvironmentTraits<jobject>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	Java type signature.
		using Signature	= ClassName<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'M', 'o', 't', 'i', 'o', 'n', 'E', 'v', 'e', 'n', 't'>;

		/// @brief	C++ native type.
		using NativeType	= Jni::Android::MotionEvent;

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

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.view.KeyEvent` object.
	class KeyEvent : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'K', 'e', 'y', 'E', 'v', 'e', 'n', 't'>;


		KeyEvent() = default;
		KeyEvent( jobject object_ref ) : Object( object_ref ) {};
		KeyEvent( const KeyEvent& other ) : Object( other ) {};
		KeyEvent( KeyEvent&& other ) : Object( other ) {};

		const KeyEvent& operator = ( jobject object_ref )		{ Object::operator=( object_ref ); return *this; };
		const KeyEvent& operator = ( const KeyEvent& other )	{ Object::operator=( other ); return *this; };
		const KeyEvent& operator = ( KeyEvent&& other )			{ Object::operator=( other ); return *this; };
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::KeyEvent` type.
	template<>
	struct NativeTypeTraits<Jni::Android::KeyEvent> : ObjectTypeTraits<Jni::Android::KeyEvent> {};
}
}

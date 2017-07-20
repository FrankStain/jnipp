// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `java.lang.Thread` object.
	class Thread : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'T', 'h', 'r', 'e', 'a', 'd'>;


		Thread() = default;
		Thread( jobject object_ref ) : Object( object_ref ) {};
		Thread( const Thread& other ) : Object( other ) {};
		Thread( Thread&& other ) : Object( other ) {};

		const Thread& operator = ( jobject object_ref )		{ Object::operator=( object_ref ); return *this; };
		const Thread& operator = ( const Thread& other )	{ Object::operator=( other ); return *this; };
		const Thread& operator = ( Thread&& other )			{ Object::operator=( other ); return *this; };
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::Thread` type.
	template<>
	struct NativeTypeTraits<Jni::Android::Thread> : ObjectTypeTraits<Jni::Android::Thread> {};
}
}

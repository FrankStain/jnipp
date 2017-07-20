// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `java.lang.ClassLoader` object.
	class ClassLoader : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's', 'L', 'o', 'a', 'd', 'e', 'r'>;


		ClassLoader() = default;
		ClassLoader( jobject object_ref ) : Object( object_ref ) {};
		ClassLoader( const ClassLoader& other ) : Object( other ) {};
		ClassLoader( ClassLoader&& other ) : Object( other ) {};

		const ClassLoader& operator = ( jobject object_ref )			{ Object::operator=( object_ref ); return *this; };
		const ClassLoader& operator = ( const ClassLoader& other )		{ Object::operator=( other ); return *this; };
		const ClassLoader& operator = ( ClassLoader&& other )			{ Object::operator=( other ); return *this; };
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::ClassLoader` type.
	template<>
	struct NativeTypeTraits<Jni::Android::ClassLoader> : ObjectTypeTraits<Jni::Android::ClassLoader> {};
}
}

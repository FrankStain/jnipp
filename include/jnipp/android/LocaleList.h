// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>
#include "LocaleList.h"


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.os.LocaleList` object.
	class LocaleList : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'o', 's', '/', 'L', 'o', 'c', 'a', 'l', 'e', 'L', 'i', 's', 't'>;


		LocaleList() = default;
		LocaleList( jobject object_ref ) : Object( object_ref ) {};
		LocaleList( const LocaleList& other ) : Object( other ) {};
		LocaleList( LocaleList&& other ) : Object( other ) {};


		/// @brief	Call of `android.os.LocaleList.isEmpty` function.
		inline const bool IsEmpty() const							{ return m_handles->is_empty.Call( *this ); };

		/// @brief	Call of `android.os.LocaleList.size` function.
		inline const int32_t GetSize() const						{ return m_handles->get_size.Call( *this ); };

		/// @brief	Call of `android.os.LocaleList.get` function.
		inline Locale GetLocale( const int32_t index ) const		{ return m_handles->get_locale.Call( *this, index ); };


		const LocaleList& operator = ( jobject object_ref )			{ Object::operator=( object_ref ); return *this; };
		const LocaleList& operator = ( const LocaleList& other )	{ Object::operator=( other ); return *this; };
		const LocaleList& operator = ( LocaleList&& other )			{ Object::operator=( other ); return *this; };

	private:
		struct LocaleListHandles
		{
			Class	jni_class	= { ClassPath::GetString() };

			MemberFunction<bool>			is_empty	= { jni_class, "isEmpty" };
			MemberFunction<int32_t>			get_size	= { jni_class, "size" };
			MemberFunction<Locale, int32_t>	get_locale	= { jni_class, "get" };
		};

		CachedHandles<LocaleListHandles>	m_handles;	// Temporally cached and shared handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::LocaleList` type.
	template<>
	struct NativeTypeTraits<Jni::Android::LocaleList> : ObjectTypeTraits<Jni::Android::LocaleList> {};
}
}

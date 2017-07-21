// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `java.util.Locale` object.
	class Locale : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<'j', 'a', 'v', 'a', '/', 'u', 't', 'i', 'l', '/', 'L', 'o', 'c', 'a', 'l', 'e'>;


		Locale() = default;
		Locale( jobject object_ref ) : Object( object_ref ) {};
		Locale( const Locale& other ) : Object( other ) {};
		Locale( Locale&& other ) : Object( other ) {};


		/// @brief	Cal the `java.util.Locale.getCountry` function.
		inline std::string GetCountry() const;

		/// @brief	Cal the `java.util.Locale.getLanguage` function.
		inline std::string GetLanguage() const;

		/// @brief	Cal the `java.util.Locale.getScript` function.
		inline std::string GetScript() const;

		/// @brief	Cal the `java.util.Locale.getVariant` function.
		inline std::string GetVariant() const;

		/// @brief	Cal the `java.util.Locale.getDisplayCountry` function.
		inline std::string GetDisplayCountry() const;

		/// @brief	Cal the `java.util.Locale.getDisplayLanguage` function.
		inline std::string GetDisplayLanguage() const;

		/// @brief	Cal the `java.util.Locale.getDisplayName` function.
		inline std::string GetDisplayName() const;

		/// @brief	Cal the `java.util.Locale.getDisplayScript` function.
		inline std::string GetDisplayScript() const;

		/// @brief	Cal the `java.util.Locale.getDisplayVariant` function.
		inline std::string GetDisplayVariant() const;

		/// @brief	Cal the `java.util.Locale.getDisplayCountry` function.
		inline std::string GetDisplayCountry( const Locale& other ) const;

		/// @brief	Cal the `java.util.Locale.getDisplayLanguage` function.
		inline std::string GetDisplayLanguage( const Locale& other ) const;

		/// @brief	Cal the `java.util.Locale.getDisplayName` function.
		inline std::string GetDisplayName( const Locale& other ) const;

		/// @brief	Cal the `java.util.Locale.getDisplayScript` function.
		inline std::string GetDisplayScript( const Locale& other ) const;

		/// @brief	Cal the `java.util.Locale.getDisplayVariant` function.
		inline std::string GetDisplayVariant( const Locale& other ) const;


		const Locale& operator = ( jobject object_ref )						{ Object::operator=( object_ref ); return *this; };
		const Locale& operator = ( const Locale& other )					{ Object::operator=( other ); return *this; };
		const Locale& operator = ( Locale&& other )							{ Object::operator=( other ); return *this; };

	private:
		struct LocaleHandles;

		CachedHandles<LocaleHandles>	m_handles;	// Temporally cached and shared handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::Locale` type.
	template<>
	struct NativeTypeTraits<Jni::Android::Locale> : ObjectTypeTraits<Jni::Android::Locale> {};
}
}

#include "Locale.inl"

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
		inline std::string GetCountry() const								{ return m_handles->get_country.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getLanguage` function.
		inline std::string GetLanguage() const								{ return m_handles->get_language.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getScript` function.
		inline std::string GetScript() const								{ return m_handles->get_script.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getVariant` function.
		inline std::string GetVariant() const								{ return m_handles->get_variant.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getDisplayCountry` function.
		inline std::string GetDisplayCountry() const						{ return m_handles->get_display_country.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getDisplayLanguage` function.
		inline std::string GetDisplayLanguage() const						{ return m_handles->get_display_lang.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getDisplayName` function.
		inline std::string GetDisplayName() const							{ return m_handles->get_display_name.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getDisplayScript` function.
		inline std::string GetDisplayScript() const							{ return m_handles->get_display_script.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getDisplayVariant` function.
		inline std::string GetDisplayVariant() const						{ return m_handles->get_display_variant.Call( *this ); };

		/// @brief	Cal the `java.util.Locale.getDisplayCountry` function.
		inline std::string GetDisplayCountry( const Locale& other ) const	{ return m_handles->get_display_country_for.Call( *this, other ); };

		/// @brief	Cal the `java.util.Locale.getDisplayLanguage` function.
		inline std::string GetDisplayLanguage( const Locale& other ) const	{ return m_handles->get_display_lang_for.Call( *this, other ); };

		/// @brief	Cal the `java.util.Locale.getDisplayName` function.
		inline std::string GetDisplayName( const Locale& other ) const		{ return m_handles->get_display_name_for.Call( *this, other ); };

		/// @brief	Cal the `java.util.Locale.getDisplayScript` function.
		inline std::string GetDisplayScript( const Locale& other ) const	{ return m_handles->get_display_script_for.Call( *this, other ); };

		/// @brief	Cal the `java.util.Locale.getDisplayVariant` function.
		inline std::string GetDisplayVariant( const Locale& other ) const	{ return m_handles->get_display_variant_for.Call( *this, other ); };


		const Locale& operator = ( jobject object_ref )						{ Object::operator=( object_ref ); return *this; };
		const Locale& operator = ( const Locale& other )					{ Object::operator=( other ); return *this; };
		const Locale& operator = ( Locale&& other )							{ Object::operator=( other ); return *this; };

	private:
		struct LocaleHandles
		{
			Class	jni_class	= { ClassPath::GetString() };

			MemberFunction<std::string>			get_country				= { jni_class, "getCountry" };
			MemberFunction<std::string>			get_display_country		= { jni_class, "getDisplayCountry" };
			MemberFunction<std::string>			get_display_lang		= { jni_class, "getDisplayLanguage" };
			MemberFunction<std::string>			get_display_name		= { jni_class, "getDisplayName" };
			MemberFunction<std::string>			get_display_script		= { jni_class, "getDisplayScript" };
			MemberFunction<std::string>			get_display_variant		= { jni_class, "getDisplayVariant" };
			MemberFunction<std::string, Locale>	get_display_country_for	= { jni_class, "getDisplayCountry" };
			MemberFunction<std::string, Locale>	get_display_lang_for	= { jni_class, "getDisplayLanguage" };
			MemberFunction<std::string, Locale>	get_display_name_for	= { jni_class, "getDisplayName" };
			MemberFunction<std::string, Locale>	get_display_script_for	= { jni_class, "getDisplayScript" };
			MemberFunction<std::string, Locale>	get_display_variant_for	= { jni_class, "getDisplayVariant" };
			MemberFunction<std::string>			get_language			= { jni_class, "getLanguage" };
			MemberFunction<std::string>			get_script				= { jni_class, "getScript" };
			MemberFunction<std::string>			get_variant				= { jni_class, "getVariant" };
		};

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

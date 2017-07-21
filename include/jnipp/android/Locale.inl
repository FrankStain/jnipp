// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Android
{
	struct Locale::LocaleHandles
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


	inline std::string Locale::GetCountry() const
	{
		return m_handles->get_country.Call( *this );
	}

	inline std::string Locale::GetLanguage() const
	{
		return m_handles->get_language.Call( *this );
	}

	inline std::string Locale::GetScript() const
	{
		return m_handles->get_script.Call( *this );
	}

	inline std::string Locale::GetVariant() const
	{
		return m_handles->get_variant.Call( *this );
	}

	inline std::string Locale::GetDisplayCountry() const
	{
		return m_handles->get_display_country.Call( *this );
	}

	inline std::string Locale::GetDisplayLanguage() const
	{
		return m_handles->get_display_lang.Call( *this );
	}

	inline std::string Locale::GetDisplayName() const
	{
		return m_handles->get_display_name.Call( *this );
	}

	inline std::string Locale::GetDisplayScript() const
	{
		return m_handles->get_display_script.Call( *this );
	}

	inline std::string Locale::GetDisplayVariant() const
	{
		return m_handles->get_display_variant.Call( *this );
	}

	inline std::string Locale::GetDisplayCountry( const Locale& other ) const
	{
		return m_handles->get_display_country_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayLanguage( const Locale& other ) const
	{
		return m_handles->get_display_lang_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayName( const Locale& other ) const
	{
		return m_handles->get_display_name_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayScript( const Locale& other ) const
	{
		return m_handles->get_display_script_for.Call( *this, other );
	}

	inline std::string Locale::GetDisplayVariant( const Locale& other ) const
	{
		return m_handles->get_display_variant_for.Call( *this, other );
	}
}
}

#include "Locale.inl"

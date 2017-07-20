// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>
#include <android/configuration.h>
#include "Configuration.const.h"
#include "Configuration.struct.h"
#include "Locale.h"


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.content.res.Configuration` object.
	class Configuration : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'c', 'o', 'n', 't', 'e', 'n', 't', '/',
			'r', 'e', 's', '/',
			'C', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', 'i', 'o', 'n'
		>;


		Configuration() = default;
		Configuration( jobject object_ref ) : Object( object_ref ) {};
		Configuration( const Configuration& other ) : Object( other ) {};
		Configuration( Configuration&& other ) : Object( other ) {};


		/// @brief	[since android-17] Getter for `android.content.res.Configuration.densityDpi` field.
		inline const int32_t GetDensityDpi() const						{ return m_handles->density_dpi.GetValue( *this, 0 ); };

		/// @brief	Getter for `android.content.res.Configuration.fontScale` field.
		inline const float GetFontScale() const							{ return m_handles->font_scale.GetValue( *this, 0.0f ); };

		/// @brief	Getter for `android.content.res.Configuration.keyboard` field.
		inline const KeyboardType GetKeyboardType() const				{ return m_handles->keyboard.GetValue( *this, KeyboardType::Undefined ); };

		/// @brief	Getter for `android.content.res.Configuration.keyboardHidden` field.
		inline const KeyboardState GetKeyboardState() const				{ return m_handles->keyboard_hidden.GetValue( *this, KeyboardState::Undefined ); };

		/// @brief	Platform-independent accessor to current locale.
		//Locale GetLocale() const;

		/// @brief	Getter for `android.content.res.Configuration.orientation` field.
		inline const ScreenOrientation GetOrientation() const			{ return m_handles->screen_orientation.GetValue( *this, ScreenOrientation::Undefined ); };

		/// @brief	Getter for `android.content.res.Configuration.screenLayout` field.
		inline ScreenLayoutState GetScreenLayout() const				{ return m_handles->scren_layout.GetValue( *this, { 0 } ); };

		/// @brief	Getter for `android.content.res.Configuration.screenWidthDp` field.
		inline const int32_t GetScreenWidthDp() const					{ return m_handles->scren_width_dp.GetValue( *this, 0 ); };

		/// @brief	Getter for `android.content.res.Configuration.screenHeightDp` field.
		inline const int32_t GetScreenHeightDp() const					{ return m_handles->scren_height_dp.GetValue( *this, 0 ); };

		/// @brief	Getter for `android.content.res.Configuration.smallestScreenWidthDp` field.
		inline const int32_t GetScreenSmallestWidthDp() const			{ return m_handles->scren_smallest_width_dp.GetValue( *this, 0 ); };

		/// @brief	Getter for `android.content.res.Configuration.uiMode` field.
		inline ScreenUiMode GetUiMode() const							{ return m_handles->ui_mode.GetValue( *this, { 0 } ); };


		const Configuration& operator = ( jobject object_ref )			{ Object::operator=( object_ref ); return *this; };
		const Configuration& operator = ( const Configuration& other )	{ Object::operator=( other ); return *this; };
		const Configuration& operator = ( Configuration&& other )		{ Object::operator=( other ); return *this; };

	private:
		struct ConfigurationHandles
		{
			Class jni_class = { ClassPath::GetString() };

			MemberField<int32_t>			density_dpi				= { jni_class, "densityDpi", IGNORE_FAILURE }; // since android-17.
			MemberField<float>				font_scale				= { jni_class, "fontScale" };
			MemberField<KeyboardType>		keyboard				= { jni_class, "keyboard" };
			MemberField<KeyboardState>		keyboard_hidden			= { jni_class, "keyboardHidden" };
			MemberField<Locale>				locale					= { jni_class, "locale", IGNORE_FAILURE }; // till android-24
			MemberField<ScreenOrientation>	screen_orientation		= { jni_class, "orientation" };
			MemberField<ScreenLayoutState>	scren_layout			= { jni_class, "screenLayout" };
			MemberField<int32_t>			scren_width_dp			= { jni_class, "screenWidthDp" };
			MemberField<int32_t>			scren_height_dp			= { jni_class, "screenHeightDp" };
			MemberField<int32_t>			scren_smallest_width_dp	= { jni_class, "smallestScreenWidthDp" };
			MemberField<ScreenUiMode>		ui_mode					= { jni_class, "uiMode" };

			//MemberFunction<LocaleList>		get_locales				= { jni_class, "getLocales", IGNORE_FAILURE }; // since android-24
		};

		CachedHandles<ConfigurationHandles>	m_handles;	// Temporally cached and shared handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::Configuration` type.
	template<>
	struct NativeTypeTraits<Jni::Android::Configuration> : ObjectTypeTraits<Jni::Android::Configuration> {};
}
}

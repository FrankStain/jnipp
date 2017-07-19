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
		Configuration() = default;
		Configuration( jobject object_ref ) : Object( object_ref ) {};
		Configuration( const Configuration& other ) : Object( other ) {};
		Configuration( Configuration&& other ) : Object( other ) {};

		const Configuration& operator = ( jobject object_ref )			{ Object::operator=( object_ref ); return *this; };
		const Configuration& operator = ( const Configuration& other )	{ Object::operator=( other ); return *this; };
		const Configuration& operator = ( Configuration&& other )		{ Object::operator=( other ); return *this; };

	private:
		struct ConfigurationHandles
		{
			Class jni_class = { "android/content/res/Configuration" };

			//MemberField<int32_t>			density_dpi				= { jni_class, "densityDpi" }; // android-17.
			MemberField<float>				font_scale				= { jni_class, "fontScale" };
			MemberField<KeyboardType>		keyboard				= { jni_class, "keyboard" };
			MemberField<KeyboardState>		keyboard_hidden			= { jni_class, "keyboardHidden" };
			MemberField<ScreenOrientation>	screen_orientation		= { jni_class, "orientation" };
			MemberField<ScreenLayoutState>	scren_layout			= { jni_class, "screenLayout" };
			MemberField<int32_t>			scren_width_dp			= { jni_class, "screenWidthDp" };
			MemberField<int32_t>			scren_height_dp			= { jni_class, "screenHeightDp" };
			MemberField<int32_t>			scren_smallest_width_dp	= { jni_class, "smallestScreenWidthDp" };
			MemberField<ScreenUiMode>		ui_mode					= { jni_class, "uiMode" };
		};

		CachedHandles<ConfigurationHandles>	m_handles;	// Temporally cached and shared handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::Configuration` type.
	template<>
	struct NativeTypeTraits<Jni::Android::Configuration> : EnvironmentTraits<jobject>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	Java type signature.
		using Signature	= ClassName<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'c', 'o', 'n', 't', 'e', 'n', 't', '/',
			'r', 'e', 's', '/',
			'C', 'o', 'n', 'f', 'i', 'g', 'u', 'r', 'a', 't', 'i', 'o', 'n'
		>;

		/// @brief	C++ native type.
		using NativeType	= Jni::Android::Configuration;

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

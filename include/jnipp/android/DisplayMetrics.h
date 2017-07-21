// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.util.DisplayMetrics` object.
	class DisplayMetrics : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<
			'a', 'n', 'd', 'r', 'o', 'i', 'd', '/',
			'u', 't', 'i', 'l', '/',
			'D', 'i', 's', 'p', 'l', 'a', 'y', 'M', 'e', 't', 'r', 'i', 'c', 's'
		>;


		DisplayMetrics() = default;
		DisplayMetrics( jobject object_ref ) : Object( object_ref ) {};
		DisplayMetrics( const DisplayMetrics& other ) : Object( other ) {};
		DisplayMetrics( DisplayMetrics&& other ) : Object( other ) {};


		/// @brief	Getter for `android.util.DisplayMetrics.density` field.
		inline const float GetDensity() const								{ return m_handles->density.GetValue( *this, 0.0f ); };

		/// @brief	Getter for `android.util.DisplayMetrics.densityDpi` field.
		inline const int32_t GetDensityDpi() const							{ return m_handles->density_dpi.GetValue( *this, 0 ); };

		/// @brief	Getter for `android.util.DisplayMetrics.scaledDensity` field.
		inline const float GetScaldDensity() const							{ return m_handles->scaled_density.GetValue( *this, 0.0f ); };

		/// @brief	Getter for `android.util.DisplayMetrics.widthPixels` field.
		inline const int32_t GetWidth() const								{ return m_handles->width_pixels.GetValue( *this, 0 ); };

		/// @brief	Getter for `android.util.DisplayMetrics.heightPixels` field.
		inline const int32_t GetHeight() const								{ return m_handles->height_pixels.GetValue( *this, 0 ); };

		/// @brief	Getter for `android.util.DisplayMetrics.xdpi` field.
		inline const float GetWidthDpi() const								{ return m_handles->width_dpi.GetValue( *this, 0.0f ); };

		/// @brief	Getter for `android.util.DisplayMetrics.ydpi` field.
		inline const float GetHeightDpi() const								{ return m_handles->height_dpi.GetValue( *this, 0.0f ); };


		const DisplayMetrics& operator = ( jobject object_ref )				{ Object::operator=( object_ref ); return *this; };
		const DisplayMetrics& operator = ( const DisplayMetrics& other )	{ Object::operator=( other ); return *this; };
		const DisplayMetrics& operator = ( DisplayMetrics&& other )			{ Object::operator=( other ); return *this; };

	private:
		struct DisplayMetricsHandles
		{
			Class	jni_class	= { ClassPath::GetString() };

			MemberField<float>		density			= { jni_class,	"density" };
			MemberField<int32_t>	density_dpi		= { jni_class,	"densityDpi" };
			MemberField<float>		scaled_density	= { jni_class,	"scaledDensity" };
			MemberField<int32_t>	width_pixels	= { jni_class,	"widthPixels" };
			MemberField<int32_t>	height_pixels	= { jni_class,	"heightPixels" };
			MemberField<float>		width_dpi		= { jni_class,	"xdpi" };
			MemberField<float>		height_dpi		= { jni_class,	"ydpi" };
		};

		CachedHandles<DisplayMetricsHandles>	m_handles;	// Temporally cached and shared handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::DisplayMetrics` type.
	template<>
	struct NativeTypeTraits<Jni::Android::DisplayMetrics> : ObjectTypeTraits<Jni::Android::DisplayMetrics> {};
}
}

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Android
{
	/// @brief	Representation of screen layout state.
	union ScreenLayoutState
	{
		int32_t		bits;				// Usable bit-set.

		struct
		{
			int32_t	screen_style : 4;	// The value, masked by `android.content.res.Configuration.SCREENLAYOUT_SIZE_MASK`.
			int32_t	wideness : 2;		// The value, masked by `android.content.res.Configuration.SCREENLAYOUT_LONG_MASK`.
			int32_t	text_direction : 2;	// The value, masked by `android.content.res.Configuration.SCREENLAYOUT_LAYOUTDIR_MASK`.
			int32_t	roundness : 2;		// The value, masked by `android.content.res.Configuration.SCREENLAYOUT_ROUND_MASK`.
		};

		struct
		{
			bool	is_small : 1;		// Result of `android.content.res.Configuration.SCREENLAYOUT_SIZE_SMALL` mask.
			bool	is_normal : 1;		// Result of `android.content.res.Configuration.SCREENLAYOUT_SIZE_NORMAL` mask.
			bool	is_xlarge : 1;		// Result of `android.content.res.Configuration.SCREENLAYOUT_SIZE_XLARGE` mask.
			bool	bit_4 : 1;			// Part of mask `android.content.res.Configuration.SCREENLAYOUT_SIZE_MASK`.
			bool	is_not_long : 1;	// Result of `android.content.res.Configuration.SCREENLAYOUT_LONG_NO` mask.
			bool	is_long : 1;		// Result of `android.content.res.Configuration.SCREENLAYOUT_LONG_YES` mask.
			bool	is_ltr : 1;			// Result of `android.content.res.Configuration.SCREENLAYOUT_LAYOUTDIR_LTR` mask.
			bool	is_rtl : 1;			// Result of `android.content.res.Configuration.SCREENLAYOUT_LAYOUTDIR_RTL` mask.
			bool	is_not_round : 1;	// Result of `android.content.res.Configuration.SCREENLAYOUT_ROUND_NO` mask.
			bool	is_round : 1;		// Result of `android.content.res.Configuration.SCREENLAYOUT_ROUND_YES` mask.
		};
	};

	/// @brief	Representation of screen UI mode.
	union ScreenUiMode
	{
		int32_t		bits;				// Usable bit-set.

		struct
		{
			int32_t	ui_type : 4;		// The value, masked by `android.content.res.Configuration.UI_MODE_TYPE_MASK`.
			int32_t	night_state : 2;	// The value, masked by `android.content.res.Configuration.UI_MODE_NIGHT_MASK`.
		};

		struct
		{
			bool	is_handed : 1;		// Result of `android.content.res.Configuration.UI_MODE_TYPE_NORMAL` mask.
			bool	is_docked : 1;		// Result of `android.content.res.Configuration.UI_MODE_TYPE_DESK` mask.
			bool	is_television : 1;	// Result of `android.content.res.Configuration.UI_MODE_TYPE_TELEVISION` mask.
			bool	bit_4 : 1;			// Part of mask `android.content.res.Configuration.`.
			bool	is_day_mode : 1;	// Result of `android.content.res.Configuration.UI_MODE_NIGHT_NO` mask.
			bool	is_night_mode : 1;	// Result of `android.content.res.Configuration.UI_MODE_NIGHT_YES` mask.
		};
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::ScreenLayoutState` type.
	template<>
	struct NativeTypeTraits<Jni::Android::ScreenLayoutState> : BitfieldTypeTraits<Jni::Android::ScreenLayoutState> {};

	/// @brief	Traits specification for native `Jni::Android::ScreenLayoutState` type.
	template<>
	struct NativeTypeTraits<Jni::Android::ScreenUiMode> : BitfieldTypeTraits<Jni::Android::ScreenUiMode> {};
}
}

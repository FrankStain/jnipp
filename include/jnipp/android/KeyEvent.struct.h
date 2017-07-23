// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Android
{
	/// @brief
	union KeyMetaState
	{
		int32_t		bits;

		struct
		{
			bool	is_shift : 1;			// 0x00000001 - android.view.KeyEvent.META_SHIFT_ON
			bool	is_alt : 1;				// 0x00000002 - android.view.KeyEvent.META_ALT_ON
			bool	is_sym : 1;				// 0x00000004 - android.view.KeyEvent.META_SYM_ON
			bool	is_function : 1;		// 0x00000008 - android.view.KeyEvent.META_FUNCTION_ON
			bool	is_left_alt : 1;		// 0x00000010 - android.view.KeyEvent.META_ALT_LEFT_ON
			bool	is_right_alt : 1;		// 0x00000020 - android.view.KeyEvent.META_ALT_RIGHT_ON
			bool	is_left_shift : 1;		// 0x00000040 - android.view.KeyEvent.META_SHIFT_LEFT_ON
			bool	is_right_shift : 1;		// 0x00000080 - android.view.KeyEvent.META_SHIFT_RIGHT_ON
			bool	reserved_1 : 1;			// 0x00000100
			bool	reserved_2 : 1;			// 0x00000200
			bool	reserved_3 : 1;			// 0x00000400
			bool	reserved_4 : 1;			// 0x00000800
			bool	is_ctrl : 1;			// 0x00001000 - android.view.KeyEvent.META_CTRL_ON
			bool	is_left_ctrl : 1;		// 0x00002000 - android.view.KeyEvent.META_CTRL_LEFT_ON
			bool	is_right_ctrl : 1;		// 0x00004000 - android.view.KeyEvent.META_CTRL_RIGHT_ON
			bool	reserved_5 : 1;			// 0x00008000
			bool	is_meta : 1;			// 0x00010000 - android.view.KeyEvent.META_META_ON
			bool	is_left_meta : 1;		// 0x00020000 - android.view.KeyEvent.META_META_LEFT_ON
			bool	is_right_meta : 1;		// 0x00040000 - android.view.KeyEvent.META_META_RIGHT_ON
			bool	reserved_6 : 1;			// 0x00080000
			bool	is_caps_lock : 1;		// 0x00100000 - android.view.KeyEvent.META_CAPS_LOCK_ON
			bool	is_num_lock : 1;		// 0x00200000 - android.view.KeyEvent.META_NUM_LOCK_ON
			bool	is_scroll_lock : 1;		// 0x00400000 - android.view.KeyEvent.META_SCROLL_LOCK_ON
		};
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::KeyMetaState` type.
	template<>
	struct NativeTypeTraits<Jni::Android::KeyMetaState> : BitfieldTypeTraits<Jni::Android::KeyMetaState> {};
}
}

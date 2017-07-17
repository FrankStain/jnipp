// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Android
{
	/// @brief	Translation of input device class.
	enum class InputSourceClass : int32_t
	{
		None		= AINPUT_SOURCE_CLASS_NONE,			// https://developer.android.com/reference/android/view/InputDevice.html#SOURCE_CLASS_NONE
		Button		= AINPUT_SOURCE_CLASS_BUTTON,		// https://developer.android.com/reference/android/view/InputDevice.html#SOURCE_CLASS_BUTTON
		Pointer		= AINPUT_SOURCE_CLASS_POINTER,		// https://developer.android.com/reference/android/view/InputDevice.html#SOURCE_CLASS_POINTER
		Navigation	= AINPUT_SOURCE_CLASS_NAVIGATION,	// https://developer.android.com/reference/android/view/InputDevice.html#SOURCE_CLASS_TRACKBALL
		Position	= AINPUT_SOURCE_CLASS_POSITION,		// https://developer.android.com/reference/android/view/InputDevice.html#SOURCE_CLASS_POSITION
		Joystick	= AINPUT_SOURCE_CLASS_JOYSTICK,		// https://developer.android.com/reference/android/view/InputDevice.html#SOURCE_CLASS_JOYSTICK
	};

	/// @brief	Translation of motion actions.
	enum class MotionActionType : int32_t
	{
		Down		= AMOTION_EVENT_ACTION_DOWN,
		Up			= AMOTION_EVENT_ACTION_UP,
		Move		= AMOTION_EVENT_ACTION_MOVE,
		Cancel		= AMOTION_EVENT_ACTION_CANCEL,
		Outside		= AMOTION_EVENT_ACTION_OUTSIDE,
		PointerDown	= AMOTION_EVENT_ACTION_POINTER_DOWN,
		PointerUp	= AMOTION_EVENT_ACTION_POINTER_UP,
		HoverMve	= AMOTION_EVENT_ACTION_HOVER_MOVE,
		Scroll		= AMOTION_EVENT_ACTION_SCROLL,
		HoverEnter	= AMOTION_EVENT_ACTION_HOVER_ENTER,
		HoverExit	= AMOTION_EVENT_ACTION_HOVER_EXIT,
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::InputSourceClass` type.
	template<>
	struct NativeTypeTraits<Jni::Android::InputSourceClass> : EnumTypeTraits<Jni::Android::InputSourceClass> {};

	/// @brief	Traits specification for native `Jni::Android::MotionActionType` type.
	template<>
	struct NativeTypeTraits<Jni::Android::MotionActionType> : EnumTypeTraits<Jni::Android::MotionActionType> {};
}
}

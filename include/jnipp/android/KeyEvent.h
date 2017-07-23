// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>
#include <android/input.h>
#include "InputDevice.const.h"
#include "KeyEvent.struct.h"


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.view.KeyEvent` object.
	class KeyEvent : public Object
	{
	public:
		/// @brief	Class path.
		using ClassPath = Jni::StaticString<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'K', 'e', 'y', 'E', 'v', 'e', 'n', 't'>;


		KeyEvent() = default;
		KeyEvent( jobject object_ref ) : Object( object_ref ) {};
		KeyEvent( const KeyEvent& other ) : Object( other ) {};
		KeyEvent( KeyEvent&& other ) : Object( other ) {};


		/// @brief	Call of `android.view.KeyEvent.getCharacters` function.
		inline std::string GetChars() const						{ return m_handles->get_chars.Call( *this ); };

		/// @brief	Call of `android.view.KeyEvent.getDisplayLabel` function.
		inline char16_t GetLabel() const						{ return m_handles->get_label.Call( *this ); };

		/// @brief	Call of `android.view.KeyEvent.getDownTime` function.
		inline std::chrono::milliseconds GetDownTIme() const	{ return std::chrono::milliseconds{ m_handles->get_down_time.Call( *this ) }; };

		/// @brief	Call of `android.view.KeyEvent.getEventTime` function.
		inline std::chrono::milliseconds GetEventTime() const	{ return std::chrono::milliseconds{ m_handles->get_event_time.Call( *this ) }; };

		/// @brief	Call of `android.view.KeyEvent.getKeyCode` function.
		inline const int32_t GetKeyCode() const					{ return m_handles->get_key_code.Call( *this ); };

		/// @brief	Call of `android.view.KeyEvent.getMetaState` function.
		inline KeyMetaState GetMetaState() const				{ return m_handles->get_meta_state.Call( *this ); };

		/// @brief	Call of `android.view.KeyEvent.getRepeatCount` function.
		inline int32_t GetScanCode() const						{ return m_handles->get_scan_code.Call( *this ); };


		const KeyEvent& operator = ( jobject object_ref )		{ Object::operator=( object_ref ); return *this; };
		const KeyEvent& operator = ( const KeyEvent& other )	{ Object::operator=( other ); return *this; };
		const KeyEvent& operator = ( KeyEvent&& other )			{ Object::operator=( other ); return *this; };

	private:
		struct KeyEventHandles
		{
			Class	jni_class	= { ClassPath::GetString() };

			MemberFunction<std::string>		get_chars		= { jni_class,	"getCharacters" };
			MemberFunction<char16_t>		get_label		= { jni_class,	"getDisplayLabel" };
			MemberFunction<int64_t>			get_down_time	= { jni_class,	"getDownTime" };
			MemberFunction<int64_t>			get_event_time	= { jni_class,	"getEventTime" };
			MemberFunction<int32_t>			get_key_code	= { jni_class,	"getKeyCode" };
			MemberFunction<KeyMetaState>	get_meta_state	= { jni_class,	"getMetaState" };
			MemberFunction<int32_t>			get_scan_code	= { jni_class,	"getRepeatCount" };
		};

		CachedHandles<KeyEventHandles, true>	m_handles;	// Permanently cached handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::KeyEvent` type.
	template<>
	struct NativeTypeTraits<Jni::Android::KeyEvent> : ObjectTypeTraits<Jni::Android::KeyEvent> {};
}
}

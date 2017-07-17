// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once

#include <jnipp/jnipp.h>
#include <android/input.h>
#include "MotionEvent.const.h"


namespace Jni
{
namespace Android
{
	/// @brief	Handle to `android.view.MotionEvent` object.
	class MotionEvent : public Object
	{
	public:
		MotionEvent() = default;
		MotionEvent( jobject object_ref ) : Object( object_ref ) {};
		MotionEvent( const MotionEvent& other ) : Object( other ) {};
		MotionEvent( MotionEvent&& other ) : Object( other ) {};


		/// @brief Get the class of input device.
		inline const InputSourceClass GetSource() const			{ return m_handles->get_source_class.Call( *this ); };

		/// @brief	Get the type of motion action, without pointer index information.
		inline const MotionActionType GetActionType() const		{ return m_handles->get_action_masked.Call( *this ); };

		/// @brief	Get the point index associated with action.
		inline const int32_t GetPointIndex() const				{ return m_handles->get_action_index.Call( *this ); };

		/// @brief	Get the number of points in event.
		inline const int32_t GetPointsCount() const				{ return m_handles->get_pointer_count.Call( *this ); };

		/// @brief	Get the time (in ms) when the user originally pressed down to start a stream of position events.
		inline const int64_t GetDownTime() const				{ return m_handles->get_down_time.Call( *this ); };


		/// @brief	Get the id of point by given index.
		inline const int32_t GetPointId( const int32_t index ) const		{ return m_handles->get_pointer_id.Call( *this, index ); };

		/// @brief	Get the X coordinate of point.
		inline const float GetPointX( const int32_t index ) const			{ return m_handles->get_pointer_x.Call( *this, index ); };

		/// @brief	Get the Y coordinate of point.
		inline const float GetPointY( const int32_t index ) const			{ return m_handles->get_pointer_y.Call( *this, index ); };

		/// @brief	Get the pressure of point.
		inline const float GetPointPressure( const int32_t index ) const	{ return m_handles->get_pointer_pressure.Call( *this, index ); };


		const MotionEvent& operator = ( jobject object_ref )		{ Object::operator=( object_ref ); return *this; };
		const MotionEvent& operator = ( const MotionEvent& other )	{ Object::operator=( other ); return *this; };
		const MotionEvent& operator = ( MotionEvent&& other )		{ Object::operator=( other ); return *this; };

	private:
		struct MotionEventHandles
		{
			Class	jni_class	= { "android/view/MotionEvent" };

			MemberFunction<int32_t>				get_pointer_count	= { jni_class, "getPointerCount" };
			MemberFunction<InputSourceClass>	get_source_class	= { jni_class, "getSource" };
			MemberFunction<MotionActionType>	get_action_masked	= { jni_class, "getActionMasked" };
			MemberFunction<int32_t>				get_action_index	= { jni_class, "getActionIndex" };
			MemberFunction<int64_t>				get_down_time		= { jni_class, "getDownTime" };

			MemberFunction<int32_t, int32_t>	get_pointer_id			= { jni_class, "" };
			MemberFunction<float, int32_t>		get_pointer_x			= { jni_class, "" };
			MemberFunction<float, int32_t>		get_pointer_y			= { jni_class, "" };
			MemberFunction<float, int32_t>		get_pointer_pressure	= { jni_class, "" };
		};

		CachedHandles<MotionEventHandles, true>	m_handles;	// Permanently cached handles for object.
	};
}

namespace Marshaling
{
	/// @brief	Traits specification for native `Jni::Android::MotionEvent` type.
	template<>
	struct NativeTypeTraits<Jni::Android::MotionEvent> : EnvironmentTraits<jobject>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	Java type signature.
		using Signature	= ClassName<'a', 'n', 'd', 'r', 'o', 'i', 'd', '/', 'v', 'i', 'e', 'w', '/', 'M', 'o', 't', 'i', 'o', 'n', 'E', 'v', 'e', 'n', 't'>;

		/// @brief	C++ native type.
		using NativeType	= Jni::Android::MotionEvent;

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

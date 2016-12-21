// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace Jni
{
namespace Marshaling
{
	/// @brief	Translation of `jobject` type.
	template<>
	struct NativeTypeInfo<jobject> final
	{
		/// @brief	C++ `jobject` type.
		using Type		= Object;
	};

	/// @brief	Translation of `Object` type.
	template<>
	struct JavaTypeInfo<Object> final
	{
		/// @brief	Java `Object` type.
		using Type		= jobject;
	};

	/// @brief	Conversion from `jobject` to `Object`.
	template<>
	inline void FromJava<Object>( const JavaType<Object>& source, Object& destination )
	{
		destination = source;
	};

	/// @brief	Conversion from `Object` to `jobject`.
	template<>
	inline void ToJava<Object>( const Object& source, JavaType<Object>& destination )
	{
		destination = *source;
	};

	/// @brief	Facade specification for transferring the `Object` objects from, and to, Java side.
	template<>
	struct JniEnvFacade<Object> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ `jobject` type.
		using NativeType	= Object;

		/// @brief	JNI representation of Java `jobject` type.
		using JavaType		= JavaType<Object>;

		/// @brief	Signature of `jobject` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `jobject` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `jobject` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `jobject` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `jobject` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};
};
};

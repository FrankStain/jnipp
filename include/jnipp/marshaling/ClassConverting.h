// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace Jni
{
namespace Marshaling
{
	/// @brief	Translation of `jclass` type.
	template<>
	struct NativeTypeInfo<jclass> final
	{
		/// @brief	C++ `jclass` type.
		using Type		= Class;
	};

	/// @brief	Translation of `Class` type.
	template<>
	struct JavaTypeInfo<Class> final
	{
		/// @brief	Java `Class` type.
		using Type		= jclass;
	};

	/// @brief	Conversion from `jclass` to `Class`.
	template<>
	inline void FromJava<Class>( const JavaType<Class>& source, Class& destination )
	{
		destination = source;
	};

	/// @brief	Conversion from `Class` to `jclass`.
	template<>
	inline void ToJava<Class>( const Class& source, JavaType<Class>& destination )
	{
		destination = *source;
	};

	/// @brief	Facade specification for transferring the `Class` objects from, and to, Java side.
	template<>
	struct JniEnvFacade<Class> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ `jclass` type.
		using NativeType	= Class;

		/// @brief	JNI representation of Java `jclass` type.
		using JavaType		= JavaType<Class>;

		/// @brief	Signature of `jclass` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `jclass` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `jclass` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `jclass` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `jclass` static fields.
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

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace Jni
{
	/// @brief	Handle to `java.lang.THread` object.
	class ThreadHandle : public ObjectHandle
	{
	public:
		ThreadHandle() = default;
		ThreadHandle( jobject object_ref ) : ObjectHandle( object_ref ) {};
		ThreadHandle( const ThreadHandle& other ) : ObjectHandle( other ) {};
		ThreadHandle( ThreadHandle&& other ) : ObjectHandle( other ) {};

		const ThreadHandle& operator = ( jobject object_ref )			{ ObjectHandle::operator=( object_ref ); return *this; };
		const ThreadHandle& operator = ( const ThreadHandle& other )	{ ObjectHandle::operator=( other ); return *this; };
		const ThreadHandle& operator = ( ThreadHandle&& other )			{ ObjectHandle::operator=( other ); return *this; };
	};

namespace Marshaling
{
	/// @brief	Translation of `ThreadHandle` type.
	template<>
	struct JavaTypeInfo<ThreadHandle> final
	{
		/// @brief	Java `ThreadHandle` type.
		using Type		= jobject;
	};

	/// @brief	Conversion from `jobject` to `ThreadHandle`.
	template<>
	inline void FromJava<ThreadHandle>( const JavaType<ThreadHandle>& source, ThreadHandle& destination )
	{
		destination = source;
	};

	/// @brief	Conversion from `ThreadHandle` to `jobject`.
	template<>
	inline void ToJava<ThreadHandle>( const ThreadHandle& source, JavaType<ThreadHandle>& destination )
	{
		destination = *source;
	};

	/// @brief	Facade specification for transferring the `ThreadHandle` objects from, and to, Java side.
	template<>
	struct JniEnvFacade<ThreadHandle> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ `jobject` type.
		using NativeType	= ThreadHandle;

		/// @brief	JNI representation of Java `jobject` type.
		using JavaType		= JavaType<ThreadHandle>;

		/// @brief	Signature of `jobject` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'T', 'h', 'r', 'e', 'a', 'd'>;

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

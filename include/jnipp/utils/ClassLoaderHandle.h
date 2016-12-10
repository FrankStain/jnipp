// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace jnipp
{
	/// @brief	Handle to `java.lang.THread` object.
	class ClassLoaderHandle : public ObjectHandle
	{
	public:
		ClassLoaderHandle() = default;
		ClassLoaderHandle( jobject object_ref ) : ObjectHandle( object_ref ) {};
		ClassLoaderHandle( const ClassLoaderHandle& other ) : ObjectHandle( other ) {};
		ClassLoaderHandle( ClassLoaderHandle&& other ) : ObjectHandle( other ) {};

		const ClassLoaderHandle& operator = ( jobject object_ref )					{ ObjectHandle::operator=( object_ref ); return *this; };
		const ClassLoaderHandle& operator = ( const ClassLoaderHandle& other )		{ ObjectHandle::operator=( other ); return *this; };
		const ClassLoaderHandle& operator = ( ClassLoaderHandle&& other )			{ ObjectHandle::operator=( other ); return *this; };
	};

namespace marshaling
{
	/// @brief	Translation of `ClassLoaderHandle` type.
	template<>
	struct JavaTypeInfo<ClassLoaderHandle> final
	{
		/// @brief	Java `ClassLoaderHandle` type.
		using Type		= jobject;
	};

	/// @brief	Conversion from `jobject` to `ClassLoaderHandle`.
	template<>
	inline void FromJava<ClassLoaderHandle>( const JavaType<ClassLoaderHandle>& source, ClassLoaderHandle& destination )
	{
		destination = source;
	};

	/// @brief	Conversion from `ClassLoaderHandle` to `jobject`.
	template<>
	inline void ToJava<ClassLoaderHandle>( const ClassLoaderHandle& source, JavaType<ClassLoaderHandle>& destination )
	{
		destination = *source;
	};

	/// @brief	Facade specification for transferring the `ClassLoaderHandle` objects from, and to, Java side.
	template<>
	struct JniEnvFacade<ClassLoaderHandle> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ `jobject` type.
		using NativeType	= ClassLoaderHandle;

		/// @brief	JNI representation of Java `jobject` type.
		using JavaType		= JavaType<ClassLoaderHandle>;

		/// @brief	Signature of `jobject` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's', 'L', 'o', 'a', 'd', 'e', 'r'>;

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

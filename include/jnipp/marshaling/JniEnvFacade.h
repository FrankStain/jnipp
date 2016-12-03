// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace marshaling
{
	template< typename TNativeType >
	struct JniEnvFacade final
	{
		static_assert( !std::is_pointer<TNativeType>::value, "The native type may not be pointer." );
		static_assert( !std::is_reference<TNativeType>::value, "The native type may not be reference." );
		static_assert( !std::is_const<TNativeType>::value, "The native type may not be const." );
		static_assert( !std::is_volatile<TNativeType>::value, "The native type may not be volatile." );

		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	C++ `object` type.
		using NativeType	= TNativeType;

		/// @brief	JNI representation of Java `object` type.
		using JavaType		= marshaling::JavaType<TNativeType>;

		/// @brief	Signature of `object` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'O', 'b', 'j', 'e', 'c', 't'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};

	template< typename TNatveType >
	using TypeSignature = typename JniEnvFacade<TNatveType>::Signature;

	template< typename TJavaType >
	using JavaTypeSignature = typename JniEnvFacade< NativeType<TJavaType> >::Signature; 

	template<>
	struct JniEnvFacade<void> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `void` type.
		using NativeType	= void;

		/// @brief	JNI representation of Java `void` type.
		using JavaType		= marshaling::JavaType<void>;

		/// @brief	Signature of `void` type.
		using Signature		= StaticString<'V'>;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallVoidMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticVoidMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualVoidMethod;
	};

	template<>
	struct JniEnvFacade<bool> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `boolean` type.
		using NativeType	= bool;

		/// @brief	JNI representation of Java `boolean` type.
		using JavaType		= marshaling::JavaType<bool>;

		/// @brief	Signature of `boolean` type.
		using Signature		= StaticString<'Z'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `boolean` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetBooleanField;

		/// @brief	Pointer to member function of `JNIEnv` to write `boolean` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetBooleanField;

		/// @brief	Pointer to member function of `JNIEnv` to read `boolean` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticBooleanField;

		/// @brief	Pointer to member function of `JNIEnv` to write `boolean` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticBooleanField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallBooleanMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticBooleanMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualBooleanMethod;
	};

	template<>
	struct JniEnvFacade<float> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `float` type.
		using NativeType	= float;

		/// @brief	JNI representation of Java `float` type.
		using JavaType		= marshaling::JavaType<float>;

		/// @brief	Signature of `float` type.
		using Signature		= StaticString<'F'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `float` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetFloatField;

		/// @brief	Pointer to member function of `JNIEnv` to write `float` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetFloatField;

		/// @brief	Pointer to member function of `JNIEnv` to read `float` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticFloatField;

		/// @brief	Pointer to member function of `JNIEnv` to write `float` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticFloatField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallFloatMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticFloatMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualFloatMethod;
	};

	template<>
	struct JniEnvFacade<double> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `double` type.
		using NativeType	= double;

		/// @brief	JNI representation of Java `double` type.
		using JavaType		= marshaling::JavaType<double>;

		/// @brief	Signature of `double` type.
		using Signature		= StaticString<'D'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `double` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetDoubleField;

		/// @brief	Pointer to member function of `JNIEnv` to write `double` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetDoubleField;

		/// @brief	Pointer to member function of `JNIEnv` to read `double` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticDoubleField;

		/// @brief	Pointer to member function of `JNIEnv` to write `double` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticDoubleField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallDoubleMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticDoubleMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualDoubleMethod;
	};

	template<>
	struct JniEnvFacade<const char*> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ plain utf8 string type.
		using NativeType	= const char*;

		/// @brief	JNI representation of Java `string` type.
		using JavaType		= marshaling::JavaType<const char*>;

		/// @brief	Signature of `string` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};

	template<>
	struct JniEnvFacade<const char16_t*> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ plain utf16 string type.
		using NativeType	= const char16_t*;

		/// @brief	JNI representation of Java `string` type.
		using JavaType		= marshaling::JavaType<const char16_t*>;

		/// @brief	Signature of `string` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};

	template<>
	struct JniEnvFacade<std::string> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ utf8 string object type.
		using NativeType	= std::string;

		/// @brief	JNI representation of Java `string` type.
		using JavaType		= marshaling::JavaType<std::string>;

		/// @brief	Signature of `string` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};

	template<>
	struct JniEnvFacade<std::u16string> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;
		
		/// @brief	C++ utf16 string object type.
		using NativeType	= std::u16string;

		/// @brief	JNI representation of Java `string` type.
		using JavaType		= marshaling::JavaType<std::u16string>;

		/// @brief	Signature of `string` type.
		using Signature		= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};

	template<>
	struct JniEnvFacade<int8_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `int8_t` type.
		using NativeType	= int8_t;

		/// @brief	JNI representation of Java `byte` type.
		using JavaType		= marshaling::JavaType<int8_t>;

		/// @brief	Signature of `byte` type.
		using Signature		= StaticString<'B'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `byte` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetByteField;

		/// @brief	Pointer to member function of `JNIEnv` to write `byte` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetByteField;

		/// @brief	Pointer to member function of `JNIEnv` to read `byte` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticByteField;

		/// @brief	Pointer to member function of `JNIEnv` to write `byte` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticByteField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallByteMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticByteMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualByteMethod;
	};

	template<>
	struct JniEnvFacade<char16_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `char16_t` type.
		using NativeType	= char16_t;

		/// @brief	JNI representation of Java `char` type.
		using JavaType		= marshaling::JavaType<char16_t>;

		/// @brief	Signature of `char` type.
		using Signature		= StaticString<'C'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `char` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetCharField;

		/// @brief	Pointer to member function of `JNIEnv` to write `char` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetCharField;

		/// @brief	Pointer to member function of `JNIEnv` to read `char` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticCharField;

		/// @brief	Pointer to member function of `JNIEnv` to write `char` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticCharField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallCharMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticCharMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualCharMethod;
	};

	template<>
	struct JniEnvFacade<int16_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `int16_t` type.
		using NativeType	= int16_t;

		/// @brief	JNI representation of Java `short` type.
		using JavaType		= marshaling::JavaType<int16_t>;

		/// @brief	Signature of `short` type.
		using Signature		= StaticString<'S'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `short` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetShortField;

		/// @brief	Pointer to member function of `JNIEnv` to write `short` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetShortField;

		/// @brief	Pointer to member function of `JNIEnv` to read `short` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticShortField;

		/// @brief	Pointer to member function of `JNIEnv` to write `short` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticShortField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallShortMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticShortMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualShortMethod;
	};

	template<>
	struct JniEnvFacade<int32_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `int32_t` type.
		using NativeType	= int32_t;

		/// @brief	JNI representation of Java `int` type.
		using JavaType		= marshaling::JavaType<int32_t>;

		/// @brief	Signature of `int` type.
		using Signature		= StaticString<'I'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `int` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetIntField;

		/// @brief	Pointer to member function of `JNIEnv` to write `int` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetIntField;

		/// @brief	Pointer to member function of `JNIEnv` to read `int` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticIntField;

		/// @brief	Pointer to member function of `JNIEnv` to write `int` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticIntField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallIntMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticIntMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualIntMethod;
	};

	template<>
	struct JniEnvFacade<int64_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `int64_t` type.
		using NativeType	= int64_t;

		/// @brief	JNI representation of Java `long` type.
		using JavaType		= marshaling::JavaType<int64_t>;

		/// @brief	Signature of `long` type.
		using Signature		= StaticString<'J'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `long` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetLongField;

		/// @brief	Pointer to member function of `JNIEnv` to write `long` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetLongField;

		/// @brief	Pointer to member function of `JNIEnv` to read `long` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticLongField;

		/// @brief	Pointer to member function of `JNIEnv` to write `long` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticLongField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallLongMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticLongMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualLongMethod;
	};

	template<>
	struct JniEnvFacade<uint8_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `uint8_t` type.
		using NativeType	= uint8_t;

		/// @brief	JNI representation of Java `short` type.
		using JavaType		= marshaling::JavaType<uint8_t>;

		/// @brief	Signature of `short` type.
		using Signature		= StaticString<'S'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `short` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetShortField;

		/// @brief	Pointer to member function of `JNIEnv` to write `short` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetShortField;

		/// @brief	Pointer to member function of `JNIEnv` to read `short` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticShortField;

		/// @brief	Pointer to member function of `JNIEnv` to write `short` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticShortField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallShortMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticShortMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualShortMethod;
	};

	template<>
	struct JniEnvFacade<uint16_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `uint16_t` type.
		using NativeType	= uint16_t;

		/// @brief	JNI representation of Java `int` type.
		using JavaType		= marshaling::JavaType<uint16_t>;

		/// @brief	Signature of `int` type.
		using Signature		= StaticString<'I'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `int` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetIntField;

		/// @brief	Pointer to member function of `JNIEnv` to write `int` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetIntField;

		/// @brief	Pointer to member function of `JNIEnv` to read `int` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticIntField;

		/// @brief	Pointer to member function of `JNIEnv` to write `int` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticIntField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallIntMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticIntMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualIntMethod;
	};

	template<>
	struct JniEnvFacade<uint32_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `uint32_t` type.
		using NativeType	= uint32_t;

		/// @brief	JNI representation of Java `long` type.
		using JavaType		= marshaling::JavaType<uint32_t>;

		/// @brief	Signature of `long` type.
		using Signature		= StaticString<'J'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `long` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetLongField;

		/// @brief	Pointer to member function of `JNIEnv` to write `long` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetLongField;

		/// @brief	Pointer to member function of `JNIEnv` to read `long` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticLongField;

		/// @brief	Pointer to member function of `JNIEnv` to write `long` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticLongField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallLongMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticLongMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualLongMethod;
	};

	template<>
	struct JniEnvFacade<uint64_t> final
	{
		/// @brief	Size of JVM local frame, required to store local reference to object.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;
		
		/// @brief	C++ `uint64_t` type.
		using NativeType	= uint64_t;

		/// @brief	JNI representation of Java `long` type.
		using JavaType		= marshaling::JavaType<uint64_t>;

		/// @brief	Signature of `long` type.
		using Signature		= StaticString<'J'>;

		/// @brief	Pointer to member function of `JNIEnv` to read `long` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetLongField;

		/// @brief	Pointer to member function of `JNIEnv` to write `long` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetLongField;

		/// @brief	Pointer to member function of `JNIEnv` to read `long` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticLongField;

		/// @brief	Pointer to member function of `JNIEnv` to write `long` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticLongField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallLongMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticLongMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualLongMethod;
	};
};
};

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

	template<>
	struct JniEnvFacade<void> final
	{
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
		
	};

	template<>
	struct JniEnvFacade<std::string> final
	{
		
	};

	template<>
	struct JniEnvFacade<int8_t> final
	{
		
	};

	template<>
	struct JniEnvFacade<int16_t> final
	{
		
	};

	template<>
	struct JniEnvFacade<int32_t> final
	{
		
	};

	template<>
	struct JniEnvFacade<int64_t> final
	{
		
	};

	template<>
	struct JniEnvFacade<uint8_t> final
	{
		
	};

	template<>
	struct JniEnvFacade<uint16_t> final
	{
		
	};

	template<>
	struct JniEnvFacade<uint32_t> final
	{
		
	};

	template<>
	struct JniEnvFacade<uint64_t> final
	{
		
	};
};
};

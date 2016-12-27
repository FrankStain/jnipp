// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Environment traits for arbitrary regular Java type.
	template< typename TJavaType >
	struct EnvironmentTraits;


	/// @brief	Traits specification for `void` type.
	template<>
	struct EnvironmentTraits<void>
	{
		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallVoidMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticVoidMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualVoidMethod;
	};

	/// @brief	Traits specification for `boolean` type.
	template<>
	struct EnvironmentTraits<jboolean>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetBooleanField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetBooleanField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticBooleanField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticBooleanField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallBooleanMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticBooleanMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualBooleanMethod;
	};

	/// @brief	Traits specification for `byte` type.
	template<>
	struct EnvironmentTraits<jbyte>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetByteField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetByteField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticByteField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticByteField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallByteMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticByteMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualByteMethod;
	};

	/// @brief	Traits specification for `char` type.
	template<>
	struct EnvironmentTraits<jchar>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetCharField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetCharField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticCharField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticCharField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallCharMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticCharMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualCharMethod;
	};

	/// @brief	Traits specification for `short` type.
	template<>
	struct EnvironmentTraits<jshort>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetShortField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetShortField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticShortField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticShortField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallShortMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticShortMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualShortMethod;
	};

	/// @brief	Traits specification for `int` type.
	template<>
	struct EnvironmentTraits<jint>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetIntField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetIntField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticIntField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticIntField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallIntMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticIntMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualIntMethod;
	};

	/// @brief	Private specification for `long` type.
	template<>
	struct EnvironmentTraits<jlong>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetLongField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetLongField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticLongField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticLongField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallLongMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticLongMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualLongMethod;
	};

	/// @brief	Private specification for `float` type.
	template<>
	struct EnvironmentTraits<jfloat>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetFloatField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetFloatField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticFloatField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticFloatField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallFloatMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticFloatMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualFloatMethod;
	};

	/// @brief	Private specification for `double` type.
	template<>
	struct EnvironmentTraits<jdouble>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetDoubleField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetDoubleField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticDoubleField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticDoubleField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallDoubleMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticDoubleMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualDoubleMethod;
	};

	/// @brief	Private specification for any type derived from `java.lang.Object`.
	template<>
	struct EnvironmentTraits<jobject>
	{
		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};
};
};

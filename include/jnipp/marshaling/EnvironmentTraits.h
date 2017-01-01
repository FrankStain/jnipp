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
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallVoidMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticVoidMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualVoidMethod;
	};

	/// @brief	Traits specification for `boolean` type.
	template<>
	struct EnvironmentTraits<jboolean>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jbooleanArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewBooleanArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetBooleanArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetBooleanArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseBooleanArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetBooleanArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetBooleanField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetBooleanField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticBooleanField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticBooleanField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallBooleanMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticBooleanMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualBooleanMethod;
	};

	/// @brief	Traits specification for `byte` type.
	template<>
	struct EnvironmentTraits<jbyte>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jbyteArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewByteArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetByteArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetByteArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseByteArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetByteArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetByteField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetByteField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticByteField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticByteField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallByteMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticByteMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualByteMethod;
	};

	/// @brief	Traits specification for `char` type.
	template<>
	struct EnvironmentTraits<jchar>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jcharArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewCharArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetCharArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetCharArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseCharArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetCharArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetCharField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetCharField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticCharField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticCharField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallCharMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticCharMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualCharMethod;
	};

	/// @brief	Traits specification for `short` type.
	template<>
	struct EnvironmentTraits<jshort>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jshortArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewShortArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetShortArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetShortArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseShortArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetShortArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetShortField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetShortField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticShortField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticShortField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallShortMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticShortMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualShortMethod;
	};

	/// @brief	Traits specification for `int` type.
	template<>
	struct EnvironmentTraits<jint>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jintArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewIntArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetIntArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetIntArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseIntArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetIntArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetIntField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetIntField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticIntField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticIntField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallIntMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticIntMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualIntMethod;
	};

	/// @brief	Private specification for `long` type.
	template<>
	struct EnvironmentTraits<jlong>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jlongArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewLongArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetLongArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetLongArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseLongArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetLongArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetLongField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetLongField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticLongField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticLongField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallLongMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticLongMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualLongMethod;
	};

	/// @brief	Private specification for `float` type.
	template<>
	struct EnvironmentTraits<jfloat>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jfloatArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewFloatArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetFloatArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetFloatArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseFloatArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetFloatArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetFloatField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetFloatField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticFloatField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticFloatField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallFloatMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticFloatMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualFloatMethod;
	};

	/// @brief	Private specification for `double` type.
	template<>
	struct EnvironmentTraits<jdouble>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= true;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jdoubleArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewDoubleArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= &JNIEnv::GetDoubleArrayElements;

		/// @brief	Array region getter.
		static constexpr auto ARRAY_REGION_READ_HANDLER			= &JNIEnv::GetDoubleArrayRegion;

		/// @brief	Array elements releaser.
		static constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= &JNIEnv::ReleaseDoubleArrayElements;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_REGION_WRITE_HANDLER		= &JNIEnv::SetDoubleArrayRegion;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetDoubleField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetDoubleField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticDoubleField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticDoubleField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallDoubleMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticDoubleMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualDoubleMethod;
	};

	/// @brief	Private specification for any type derived from `java.lang.Object`.
	template<>
	struct EnvironmentTraits<jobject>
	{
		/// @brief	Is this type plain?
		static constexpr bool IS_PLAIN							= false;

		/// @brief	Type of JNI array representation, which can be consumed by array functions.
		using JavaArrayType										= jobjectArray;

		/// @brief	Array allocator.
		static constexpr auto ARRAY_CONSTRUCT_HANDLER			= &JNIEnv::NewObjectArray;

		/// @brief	Array elements getter.
		static constexpr auto ARRAY_ELEMENT_READ_HANDLER		= &JNIEnv::GetObjectArrayElement;

		/// @brief	Array region setter.
		static constexpr auto ARRAY_ELEMENT_WRITE_HANDLER		= &JNIEnv::SetObjectArrayElement;

		/// @brief	Member-fields regular reader.
		static constexpr auto FIELD_READ_HANDLER				= &JNIEnv::GetObjectField;

		/// @brief	Member-fields regular writer.
		static constexpr auto FIELD_WRITE_HANDLER				= &JNIEnv::SetObjectField;

		/// @brief	Static fields regular reader.
		static constexpr auto STATIC_FIELD_READ_HANDLER			= &JNIEnv::GetStaticObjectField;

		/// @brief	Static fields regular writer.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER		= &JNIEnv::SetStaticObjectField;

		/// @brief	Member-function regular invocation.
		static constexpr auto FUNCTION_HANDLER					= &JNIEnv::CallObjectMethod;

		/// @brief	Static function regular invocation.
		static constexpr auto STATIC_FUNCTION_HANDLER			= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Member-function non-virtual invocation.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER		= &JNIEnv::CallNonvirtualObjectMethod;
	};
};
};

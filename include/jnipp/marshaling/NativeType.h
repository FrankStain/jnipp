// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace marshaling
{
	/**
		@brief	Information about transformation from Java type to C++ one.
		@tparam	TJavaType	JNI representation for Java type.
	*/
	template< typename TJavaType >
	struct NativeTypeInfo;

	/// @brief	Translation from JNI representation of Java type into C++ native type.
	template< typename TJavaType >
	using NativeType = typename NativeTypeInfo<TJavaType>::Type;


	/// @brief	Translation of `void` type.
	template<>
	struct NativeTypeInfo<void> final
	{
		/// @brief	C++ `void` type.
		using Type		= void;
	};

	/// @brief	Translation of `boolean` type.
	template<>
	struct NativeTypeInfo<jboolean> final
	{
		/// @brief	C++ `boolean` type.
		using Type		= bool;
	};

	/// @brief	Translation of `string` type.
	template<>
	struct NativeTypeInfo<jstring> final
	{
		/// @brief	C++ `string` type.
		using Type		= std::string;
	};

	/// @brief	Translation of `float` type.
	template<>
	struct NativeTypeInfo<jfloat> final
	{
		/// @brief	C++ `float` type.
		using Type		= float;
	};

	/// @brief	Translation of `double` type.
	template<>
	struct NativeTypeInfo<jdouble> final
	{
		/// @brief	C++ `double` type.
		using Type		= double;
	};

	/// @brief	Translation of `byte` type.
	template<>
	struct NativeTypeInfo<jbyte> final
	{
		/// @brief	C++ `byte` type.
		using Type		= int8_t;
	};

	/// @brief	Translation of `char` type.
	template<>
	struct NativeTypeInfo<jchar> final
	{
		/// @brief	C++ `char` type.
		using Type		= char16_t;
	};

	/// @brief	Translation of `short` type.
	template<>
	struct NativeTypeInfo<jshort> final
	{
		/// @brief	C++ `short` type.
		using Type		= int16_t;
	};

	/// @brief	Translation of `int` type.
	template<>
	struct NativeTypeInfo<jint> final
	{
		/// @brief	C++ `int` type.
		using Type		= int32_t;
	};

	/// @brief	Translation of `long` type.
	template<>
	struct NativeTypeInfo<jlong> final
	{
		/// @brief	C++ `long` type.
		using Type		= int64_t;
	};
};
};

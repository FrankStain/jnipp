// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace marshaling
{
	/**
		@brief	Information about transformation from C++ type to Java one.
		@tparam	TNativeType	C++ native type.
	*/
	template< typename TNativeType >
	struct JavaTypeInfo;

	/// @brief	Translation from JNI representation of Java type into Java native type.
	template< typename TNativeType >
	using JavaType = typename JavaTypeInfo<TNativeType>::Type;

	/// @brief	Translation of `void` type.
	template<>
	struct JavaTypeInfo<void> final
	{
		/// @brief	Java `void` type.
		using Type		= void;
	};

	/// @brief	Translation of `bool` type.
	template<>
	struct JavaTypeInfo<bool> final
	{
		/// @brief	Java `boolean` type.
		using Type		= jboolean;
	};

	/// @brief	Translation of `string` type.
	template<>
	struct JavaTypeInfo<const char*> final
	{
		/// @brief	Java `string` type.
		using Type		= jstring;
	};

	/// @brief	Translation of `string` type.
	template<>
	struct JavaTypeInfo<std::string> final
	{
		/// @brief	Java `string` type.
		using Type		= jstring;
	};

	/// @brief	Translation of `float` type.
	template<>
	struct JavaTypeInfo<float> final
	{
		/// @brief	Java `float` type.
		using Type		= jfloat;
	};

	/// @brief	Translation of `double` type.
	template<>
	struct JavaTypeInfo<double> final
	{
		/// @brief	Java `double` type.
		using Type		= jdouble;
	};

	/// @brief	Translation of `int8_t` type.
	template<>
	struct JavaTypeInfo<int8_t> final
	{
		/// @brief	Java `byte` type.
		using Type		= jbyte;
	};

	/// @brief	Translation of `char16_t` type.
	template<>
	struct JavaTypeInfo<char16_t> final
	{
		/// @brief	Java `char` type.
		using Type		= jchar;
	};

	/// @brief	Translation of `int16_t` type.
	template<>
	struct JavaTypeInfo<int16_t> final
	{
		/// @brief	Java `short` type.
		using Type		= jshort;
	};

	/// @brief	Translation of `int32_t` type.
	template<>
	struct JavaTypeInfo<int32_t> final
	{
		/// @brief	Java `int` type.
		using Type		= jint;
	};

	/// @brief	Translation of `int64_t` type.
	template<>
	struct JavaTypeInfo<int64_t> final
	{
		/// @brief	Java `long` type.
		using Type		= jlong;
	};

	/// @brief	Translation of `uint8_t` type.
	template<>
	struct JavaTypeInfo<uint8_t> final
	{
		/// @brief	Java `byte` type.
		using Type		= jshort;
	};

	/// @brief	Translation of `uint16_t` type.
	template<>
	struct JavaTypeInfo<uint16_t> final
	{
		/// @brief	Java `short` type.
		using Type		= jint;
	};

	/// @brief	Translation of `uint32_t` type.
	template<>
	struct JavaTypeInfo<uint32_t> final
	{
		/// @brief	Java `int` type.
		using Type		= jlong;
	};

	/// @brief	Translation of `uint64_t` type.
	template<>
	struct JavaTypeInfo<uint64_t> final
	{
		/// @brief	Java `long` type.
		using Type		= jlong;
	};
};
};

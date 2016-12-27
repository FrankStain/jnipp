// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Traits for arbitrary regular Java type.
	template< typename TJavaType >
	struct JavaTypeTraits;

	
	/// @brief	Signature of arbitrary regular Java type.
	template< typename TJavaType >
	using JavaTypeSignature = typename JavaTypeTraits<TJavaType>::Signature;

	/// @brief	Signature of function, which uses regular Java types.
	template< typename TJavaReturnType, typename... TJavaArgumentTypes >
	using JavaFunctionSignature = FunctionSignature<JavaTypeSignature<TJavaReturnType>, JavaTypeSignature<TJavaArgumentTypes>...>;


	/// @brief	Traits specification for `void` type.
	template<>
	struct JavaTypeTraits<void>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'V'>;
	};

	/// @brief	Traits specification for `boolean` type.
	template<>
	struct JavaTypeTraits<jboolean>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'Z'>;
	};

	/// @brief	Traits specification for `byte` type.
	template<>
	struct JavaTypeTraits<jbyte>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'B'>;
	};

	/// @brief	Traits specification for `char` type.
	template<>
	struct JavaTypeTraits<jchar>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'C'>;
	};

	/// @brief	Traits specification for `short` type.
	template<>
	struct JavaTypeTraits<jshort>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'S'>;
	};

	/// @brief	Traits specification for `int` type.
	template<>
	struct JavaTypeTraits<jint>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'I'>;
	};

	/// @brief	Traits specification for `long` type.
	template<>
	struct JavaTypeTraits<jlong>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'J'>;
	};

	/// @brief	Traits specification for `float` type.
	template<>
	struct JavaTypeTraits<jfloat>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'F'>;
	};

	/// @brief	Traits specification for `double` type.
	template<>
	struct JavaTypeTraits<jdouble>
	{
		/// @brief	Java type signature.
		using Signature	= StaticString<'D'>;
	};

	/// @brief	Traits specification for `java.lang.Object` type.
	template<>
	struct JavaTypeTraits<jobject>
	{
		/// @brief	Java type signature.
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'O', 'b', 'j', 'e', 'c', 't'>;
	};

	/// @brief	Traits specification for `java.lang.Class` type.
	template<>
	struct JavaTypeTraits<jclass>
	{
		/// @brief	Java type signature.
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's'>;
	};

	/// @brief	Traits specification for `java.lang.String` type.
	template<>
	struct JavaTypeTraits<jstring>
	{
		/// @brief	Java type signature.
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;
	};
};
};

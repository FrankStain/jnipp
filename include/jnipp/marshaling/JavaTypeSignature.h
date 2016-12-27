// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	template< typename TJavaType >
	struct JavaTypeTraits;

	
	template< typename TJavaType >
	using JavaTypeSignature	= typename JavaTypeTraits<TJavaType>::Signature;

	template< typename TJavaReturnType, typename... TJavaArgumentTypes >
	using JavaFunctionSignature	= FunctionSignature<JavaTypeSignature<TJavaReturnType>, JavaTypeSignature<TJavaArgumentTypes>...>;


	template<>
	struct JavaTypeTraits<void>
	{
		using Signature	= StaticString<'V'>;
	};

	template<>
	struct JavaTypeTraits<jboolean>
	{
		using Signature	= StaticString<'Z'>;
	};

	template<>
	struct JavaTypeTraits<jbyte>
	{
		using Signature	= StaticString<'B'>;
	};

	template<>
	struct JavaTypeTraits<jchar>
	{
		using Signature	= StaticString<'C'>;
	};

	template<>
	struct JavaTypeTraits<jshort>
	{
		using Signature	= StaticString<'S'>;
	};

	template<>
	struct JavaTypeTraits<jint>
	{
		using Signature	= StaticString<'I'>;
	};

	template<>
	struct JavaTypeTraits<jlong>
	{
		using Signature	= StaticString<'J'>;
	};

	template<>
	struct JavaTypeTraits<jfloat>
	{
		using Signature	= StaticString<'F'>;
	};

	template<>
	struct JavaTypeTraits<jdouble>
	{
		using Signature	= StaticString<'D'>;
	};

	template<>
	struct JavaTypeTraits<jobject>
	{
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'O', 'b', 'j', 'e', 'c', 't'>;
	};

	template<>
	struct JavaTypeTraits<jclass>
	{
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'C', 'l', 'a', 's', 's'>;
	};

	template<>
	struct JavaTypeTraits<jstring>
	{
		using Signature	= ClassName<'j', 'a', 'v', 'a', '/', 'l', 'a', 'n', 'g', '/', 'S', 't', 'r', 'i', 'n', 'g'>;
	};
};
};

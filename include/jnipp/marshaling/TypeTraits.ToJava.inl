// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	inline void TypeTraits<bool>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = ( source )? JNI_TRUE : JNI_FALSE;
	};

	inline void TypeTraits<const char*>::ToJava( const NativeType& source, JavaType& destination )
	{
		auto local_env	= VirtualMachine::GetLocalEnvironment();
		destination		= local_env->NewStringUTF( source );
	};

	inline void TypeTraits<const char16_t*>::ToJava( const NativeType& source, JavaType& destination )
	{
		auto local_env	= VirtualMachine::GetLocalEnvironment();
		destination		= local_env->NewString( reinterpret_cast<const jchar*>( source ), std::char_traits<char16_t>::length( source ) );
	};

	inline void TypeTraits<std::string>::ToJava( const NativeType& source, JavaType& destination )
	{
		ToJava( source.c_str(), destination );
	};

	inline void TypeTraits<std::u16string>::ToJava( const NativeType& source, JavaType& destination )
	{
		ToJava( source.c_str(), destination );
	};

	inline void TypeTraits<float>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<double>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int8_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<char16_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int16_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int32_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int64_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint8_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint16_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint32_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint64_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = reinterpret_cast<const int64_t&>( source );
	};
};
};

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	inline void TypeTraits<bool>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source == JNI_TRUE;
	};

	inline void TypeTraits<std::string>::FromJava( const JavaType& source, NativeType& destination )
	{
		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringUTFLength( source );

		destination.clear();
		JNI_RETURN_IF( string_length == 0 );

		destination.resize( string_length, ' ' );
		local_env->GetStringUTFRegion( source, 0, string_length, &destination.front() );
	};

	inline void TypeTraits<std::u16string>::FromJava( const JavaType& source, NativeType& destination )
	{
		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringLength( source );

		destination.clear();
		JNI_RETURN_IF( string_length == 0 );

		destination.resize( string_length, ' ' );
		local_env->GetStringRegion( source, 0, string_length, reinterpret_cast<jchar*>( &destination.front() ) );
	};

	inline void TypeTraits<float>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<double>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int8_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<char16_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int16_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int32_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<int64_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint8_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint16_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint32_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void TypeTraits<uint64_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};
};
};

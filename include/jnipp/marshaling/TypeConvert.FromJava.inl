// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	template<>
	inline void FromJava<bool>( const JavaType<bool>& source, bool& destination )
	{
		destination = source == JNI_TRUE;
	};

	template<>
	inline void FromJava<std::string>( const JavaType<std::string>& source, std::string& destination )
	{
		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringUTFLength( source );

		destination.clear();
		JNI_RETURN_IF( string_length == 0 );

		destination.resize( string_length, ' ' );
		local_env->GetStringUTFRegion( source, 0, string_length, &destination.front() );
	};

	template<>
	inline void FromJava<std::u16string>( const JavaType<std::u16string>& source, std::u16string& destination )
	{
		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringLength( source );

		destination.clear();
		JNI_RETURN_IF( string_length == 0 );

		destination.resize( string_length, ' ' );
		local_env->GetStringRegion( source, 0, string_length, reinterpret_cast<jchar*>( &destination.front() ) );
	};

	template<>
	inline void FromJava<float>( const JavaType<float>& source, float& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<double>( const JavaType<double>& source, double& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<int8_t>( const JavaType<int8_t>& source, int8_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<char16_t>( const JavaType<char16_t>& source, char16_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<int16_t>( const JavaType<int16_t>& source, int16_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<int32_t>( const JavaType<int32_t>& source, int32_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<int64_t>( const JavaType<int64_t>& source, int64_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<uint8_t>( const JavaType<uint8_t>& source, uint8_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<uint16_t>( const JavaType<uint16_t>& source, uint16_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<uint32_t>( const JavaType<uint32_t>& source, uint32_t& destination )
	{
		destination = source;
	};

	template<>
	inline void FromJava<uint64_t>( const JavaType<uint64_t>& source, uint64_t& destination )
	{
		destination = source;
	};
};
};

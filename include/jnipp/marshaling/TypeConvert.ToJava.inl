// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace marshaling
{
	template<>
	inline void ToJava<bool>( const bool& source, JavaType<bool>& destination )
	{
		destination = ( source )? JNI_TRUE : JNI_FALSE;
	};

	template<>
	inline void ToJava<const char*>( const char* const& source, JavaType<const char*>& destination )
	{
		// @TODO: Make convert using `JniEnvironment`.
	};

	template<>
	inline void ToJava<const char16_t*>( const char16_t* const& source, JavaType<const char16_t*>& destination )
	{
		// @TODO: Make convert using `JniEnvironment`.
	};

	template<>
	inline void ToJava<std::string>( const std::string& source, JavaType<std::string>& destination )
	{
		// @TODO: Make convert using `JniEnvironment`.
	};

	template<>
	inline void ToJava<std::u16string>( const std::u16string& source, JavaType<std::u16string>& destination )
	{
		// @TODO: Make convert using `JniEnvironment`.
	};

	template<>
	inline void ToJava<float>( const float& source, JavaType<float>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<double>( const double& source, JavaType<double>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<int8_t>( const int8_t& source, JavaType<int8_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<char16_t>( const char16_t& source, JavaType<char16_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<int16_t>( const int16_t& source, JavaType<int16_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<int32_t>( const int32_t& source, JavaType<int32_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<int64_t>( const int64_t& source, JavaType<int64_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<uint8_t>( const uint8_t& source, JavaType<uint8_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<uint16_t>( const uint16_t& source, JavaType<uint16_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<uint32_t>( const uint32_t& source, JavaType<uint32_t>& destination )
	{
		destination = source;
	};

	template<>
	inline void ToJava<uint64_t>( const uint64_t& source, JavaType<uint64_t>& destination )
	{
		destination = reinterpret_cast<const int64_t&>( source );
	};
};
};

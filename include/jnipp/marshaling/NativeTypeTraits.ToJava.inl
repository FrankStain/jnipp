// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	inline void NativeTypeTraits<bool>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = ( source )? JNI_TRUE : JNI_FALSE;
	}

	inline void NativeTypeTraits<const char*>::ToJava( const NativeType& source, JavaType& destination )
	{
		auto local_env	= VirtualMachine::GetLocalEnvironment();
		destination		= local_env->NewStringUTF( source );
	}

	inline void NativeTypeTraits<const char16_t*>::ToJava( const NativeType& source, JavaType& destination )
	{
		auto local_env	= VirtualMachine::GetLocalEnvironment();
		destination		= local_env->NewString( reinterpret_cast<const jchar*>( source ), std::char_traits<char16_t>::length( source ) );
	}

	inline void NativeTypeTraits<std::string>::ToJava( const NativeType& source, JavaType& destination )
	{
		NativeTypeTraits<const char*>::ToJava( source.c_str(), destination );
	}

	inline void NativeTypeTraits<std::u16string>::ToJava( const NativeType& source, JavaType& destination )
	{
		NativeTypeTraits<const char16_t*>::ToJava( source.c_str(), destination );
	}

	inline void NativeTypeTraits<float>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<double>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<int8_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<char16_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<int16_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<int32_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<int64_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<uint8_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<uint16_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<uint32_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = source;
	}

	inline void NativeTypeTraits<uint64_t>::ToJava( const NativeType& source, JavaType& destination )
	{
		destination = reinterpret_cast<const int64_t&>( source );
	}

	template< typename TNativeElementType, typename TAllocatorType >
	inline void NativeTypeTraits<std::vector<TNativeElementType, TAllocatorType>>::ToJava( const NativeType& source, JavaType& destination )
	{
		using ElementTraits		= NativeTypeTraits<TNativeElementType>;
		using JavaArrayType		= typename ElementTraits::JavaArrayType;
		using TranslationTraits	= ArrayTranslationTraits<ElementTraits>;

		TranslationTraits::ToJava( source, reinterpret_cast<JavaArrayType&>( destination ) );
	}
}
}

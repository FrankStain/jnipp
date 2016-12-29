// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	inline void NativeTypeTraits<bool>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source == JNI_TRUE;
	};

	inline void NativeTypeTraits<std::string>::FromJava( const JavaType& source, NativeType& destination )
	{
		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringUTFLength( source );

		destination.clear();
		JNI_RETURN_IF( string_length == 0 );

		destination.resize( static_cast<size_t>( string_length ), ' ' );
		local_env->GetStringUTFRegion( source, 0, string_length, &destination.front() );
	};

	inline void NativeTypeTraits<std::u16string>::FromJava( const JavaType& source, NativeType& destination )
	{
		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize string_length	= local_env->GetStringLength( source );

		destination.clear();
		JNI_RETURN_IF( string_length == 0 );

		destination.resize( static_cast<size_t>( string_length ), ' ' );
		local_env->GetStringRegion( source, 0, string_length, reinterpret_cast<jchar*>( &destination.front() ) );
	};

	inline void NativeTypeTraits<float>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<double>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<int8_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<char16_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<int16_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<int32_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<int64_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<uint8_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<uint16_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<uint32_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	inline void NativeTypeTraits<uint64_t>::FromJava( const JavaType& source, NativeType& destination )
	{
		destination = source;
	};

	template< typename TNativeElementType, typename TAllocatorType >
	inline void NativeTypeTraits<std::vector<TNativeElementType, TAllocatorType>>::FromJava( const JavaType& source, NativeType& destination )
	{
		using ElementTraits = NativeTypeTraits<TNativeElementType>;

		destination.clear();

		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize array_length	= local_env->GetArrayLength( source );
		JNI_RETURN_IF( array_length == 0 );

		destination.reserve( static_cast<size_t>( array_length ) );
		if( ElementTraits::IS_PLAIN )
		{
			constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= ElementTraits::ARRAY_ELEMENTS_ACQUIRE_HANDLER;
			constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= ElementTraits::ARRAY_ELEMENTS_RELEASE_HANDLER;

			auto array_elements = (local_env->*ARRAY_ELEMENTS_ACQUIRE_HANDLER)( source, nullptr );
			JNI_RETURN_IF_E( array_elements == nullptr, , "Failed to read elements of array." );

			std::transform(
				array_elements, array_elements + array_length, std::back_inserter( destination ),
				[]( const typename ElementTraits::JavaType& stored_value )
				{
					return Jni::Marshaling::FromJava<TNativeElementType>( stored_value );
				}
			);

			(local_env->*ARRAY_ELEMENTS_RELEASE_HANDLER)( source, array_elements, JNI_ABORT );
		}
		else
		{
			constexpr auto ARRAY_ELEMENT_READ_HANDLER = ElementTraits::ARRAY_ELEMENT_READ_HANDLER;

			for( jsize element_index = 0; element_index < array_length; ++element_index )
			{
				auto element = (local_env->*ARRAY_ELEMENT_READ_HANDLER)( source, element_index );
				destination.emplace_back( Jni::Marshaling::FromJava<TNativeElementType>( element ) );
			};
		};
	};
};
};

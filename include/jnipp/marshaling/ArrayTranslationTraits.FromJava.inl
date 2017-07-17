// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	template< typename TElementTraits, bool IS_ELEMENT_PLAIN >
	template< typename TAllocatorType >
	inline void ArrayTranslationTraits<TElementTraits, IS_ELEMENT_PLAIN>::FromJava( const JavaType& source, NativeType<TAllocatorType>& destination )
	{
		constexpr auto ARRAY_ELEMENT_READ_HANDLER = TElementTraits::ARRAY_ELEMENT_READ_HANDLER;

		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize array_length	= local_env->GetArrayLength( source );
		JNI_RETURN_IF( array_length == 0 );

		destination.reserve( static_cast<size_t>( array_length ) );

		local_env->PushLocalFrame( TElementTraits::LOCAL_FRAME_SIZE * array_length );
		for( jsize element_index = 0; element_index < array_length; ++element_index )
		{
			auto element = static_cast<ElementJavaType>( (local_env->*ARRAY_ELEMENT_READ_HANDLER)( source, element_index ) );
			destination.emplace_back( Jni::Marshaling::FromJava<ElementNativeType>( element ) );
		}
		local_env->PopLocalFrame( nullptr );
	}

	template< typename TElementTraits >
	template< typename TAllocatorType >
	inline void ArrayTranslationTraits<TElementTraits, true>::FromJava( const JavaType& source, NativeType<TAllocatorType>& destination )
	{
		constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= TElementTraits::ARRAY_ELEMENTS_ACQUIRE_HANDLER;
		constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= TElementTraits::ARRAY_ELEMENTS_RELEASE_HANDLER;

		auto local_env				= VirtualMachine::GetLocalEnvironment();
		const jsize array_length	= local_env->GetArrayLength( source );
		JNI_RETURN_IF( array_length == 0 );

		destination.reserve( static_cast<size_t>( array_length ) );

		auto array_elements = (local_env->*ARRAY_ELEMENTS_ACQUIRE_HANDLER)( source, nullptr );
		JNI_RETURN_IF_E( array_elements == nullptr, , "Failed to read elements of array." );

		std::transform(
			array_elements, array_elements + array_length, std::back_inserter( destination ),
			[]( const typename TElementTraits::JavaType& stored_value )
			{
				return Jni::Marshaling::FromJava<ElementNativeType>( stored_value );
			}
		);

		(local_env->*ARRAY_ELEMENTS_RELEASE_HANDLER)( source, array_elements, JNI_ABORT );
	}
}
}

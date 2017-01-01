// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	template< typename TElementTraits, bool IS_ELEMENT_PLAIN >
	template< typename TAllocatorType >
	inline void ArrayTranslationTraits<TElementTraits, IS_ELEMENT_PLAIN>::ToJava( const NativeType<TAllocatorType>& source, JavaType& destination )
	{
		using ElementSignature	= typename TElementTraits::Signature;
		
		constexpr auto ARRAY_CONSTRUCT_HANDLER		= TElementTraits::ARRAY_CONSTRUCT_HANDLER;
		constexpr auto ARRAY_ELEMENT_WRITE_HANDLER	= TElementTraits::ARRAY_ELEMENT_WRITE_HANDLER;

		auto local_env = VirtualMachine::GetLocalEnvironment();

		const Class element_class{ ClassPath<ElementSignature>::GetString() };

		destination = (local_env->*ARRAY_CONSTRUCT_HANDLER)( static_cast<jsize>( source.size() ), *element_class, nullptr );
		JNI_RETURN_IF( source.empty() );

		jsize element_index = 0;
		local_env->PushLocalFrame( TElementTraits::LOCAL_FRAME_SIZE * source.size() );
		for( const auto& stored_element : source )
		{
			(local_env->*ARRAY_ELEMENT_WRITE_HANDLER)( destination, element_index++, Jni::Marshaling::ToJava<ElementNativeType>( stored_element ) );
		};
		local_env->PopLocalFrame( nullptr );
	};

	template< typename TElementTraits >
	template< typename TAllocatorType >
	inline void ArrayTranslationTraits<TElementTraits, true>::ToJava( const NativeType<TAllocatorType>& source, JavaType& destination )
	{
		constexpr auto ARRAY_CONSTRUCT_HANDLER			= TElementTraits::ARRAY_CONSTRUCT_HANDLER;
		constexpr auto ARRAY_ELEMENTS_ACQUIRE_HANDLER	= TElementTraits::ARRAY_ELEMENTS_ACQUIRE_HANDLER;
		constexpr auto ARRAY_ELEMENTS_RELEASE_HANDLER	= TElementTraits::ARRAY_ELEMENTS_RELEASE_HANDLER;

		auto local_env = VirtualMachine::GetLocalEnvironment();

		destination = (local_env->*ARRAY_CONSTRUCT_HANDLER)( static_cast<jsize>( source.size() ) );
		JNI_RETURN_IF( source.empty() );

		auto array_elements = (local_env->*ARRAY_ELEMENTS_ACQUIRE_HANDLER)( destination, nullptr );
		JNI_RETURN_IF_E( array_elements == nullptr, , "Failed to read elements of array." );

		std::transform(
			source.begin(), source.end(), array_elements,
			[]( const ElementNativeType& stored_value )
			{
				return Jni::Marshaling::ToJava<ElementNativeType>( stored_value );
			}
		);

		(local_env->*ARRAY_ELEMENTS_RELEASE_HANDLER)( destination, array_elements, JNI_OK );
	};
};
};

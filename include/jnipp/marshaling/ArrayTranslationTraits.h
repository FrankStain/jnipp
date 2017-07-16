// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	template< typename TElementTraits, bool IS_ELEMENT_PLAIN = TElementTraits::IS_PLAIN >
	struct ArrayTranslationTraits final
	{
		using ElementJavaType	= typename TElementTraits::JavaType;

		using ElementNativeType	= typename TElementTraits::NativeType;

		using JavaType			= typename TElementTraits::JavaArrayType;

		template< typename TAllocatorType >
		using NativeType		= std::vector<typename TElementTraits::NativeType, TAllocatorType>;

		template< typename TAllocatorType >
		static inline void FromJava( const JavaType& source, NativeType<TAllocatorType>& destination );

		template< typename TAllocatorType >
		static inline void ToJava( const NativeType<TAllocatorType>& source, JavaType& destination );
	};

	template< typename TElementTraits >
	struct ArrayTranslationTraits<TElementTraits, true> final
	{
		using ElementJavaType	= typename TElementTraits::JavaType;

		using ElementNativeType	= typename TElementTraits::NativeType;

		using JavaType			= typename TElementTraits::JavaArrayType;

		template< typename TAllocatorType >
		using NativeType		= std::vector<typename TElementTraits::NativeType, TAllocatorType>;

		template< typename TAllocatorType >
		static inline void FromJava( const JavaType& source, NativeType<TAllocatorType>& destination );

		template< typename TAllocatorType >
		static inline void ToJava( const NativeType<TAllocatorType>& source, JavaType& destination );
	};
};
};

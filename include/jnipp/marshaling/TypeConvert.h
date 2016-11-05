// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace marshaling
{
	/**
		@brief	Regular converting function from Java type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, Java-side.
		@param	destination	Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline void FromJava( const JavaType<TNativeType>& source, TNativeType& destination );

	/**
		@brief	Regular converting function from C++ type to Java one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@param	destination	Final storage of converted value, Java-side.
	*/
	template< typename TNativeType >
	inline void ToJava( const TNativeType& source, JavaType<TNativeType>& destination );

	/**
		@brief	NRVO-optimizable converting function from Java type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, Java-side.
		@return				Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline TNativeType FromJava( const JavaType<TNativeType>& source )
	{
		TNativeType destination;
		FromJava( source, destination );
		return destination;
	};

	/**
		@brief	NRVO-optimizable converting function from C++ type to Java one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@return				Final storage of converted value, Java-side.
	*/
	template< typename TNativeType >
	inline JavaType<TNativeType> ToJava( const TNativeType& source )
	{
		JavaType<TNativeType> destination;
		ToJava( source, destination );
		return destination;
	};
};
};

#include "TypeConvert.FromJava.inl"
#include "TypeConvert.ToJava.inl"

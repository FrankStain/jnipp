// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
{
	template< size_t... NUMBERS >
	struct NumberSumm;

	template< size_t NUMBER, size_t... REST_NUMBERS >
	struct NumberSumm<NUMBER, REST_NUMBERS...>
	{
		constexpr static const size_t RESULT = NUMBER + NumberSumm<REST_NUMBERS...>::RESULT;
	};

	template< size_t NUMBER >
	struct NumberSumm<NUMBER>
	{
		constexpr static const size_t RESULT = NUMBER;
	};

	template<>
	struct NumberSumm<>
	{
		constexpr static const size_t RESULT = 0;
	};

	template< typename... TNativeTypes >
	struct TotalLocalFrame : NumberSumm<Jni::Marshaling::TypeTraits<TNativeTypes>::LOCAL_FRAME_SIZE...>
	{
	
	};
};
};

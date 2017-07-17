// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/**
		@brief	Compile-time string. While runtime instances of one will be represented by plain strings.
		@note	Using of compile-time strings for deducing signatures of functions save runtime performance.
		`StaicString` is represented by variadic number of chars. In this form it's much easier to combine such strings.
	*/
	template< char... CHARS >
	struct StaticString final
	{
		/// @brief	Get the plain string from stored chars.
		inline static const char* GetString()
		{
			static const char string[] = { CHARS..., 0 };
			return string;
		}
	};
}

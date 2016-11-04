// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace utils
{
	/**
		@brief	Combiner of static strings.
		This class is useful for concatenation of multiple static strings in one.
		@tparam	TStrings	Chain of static strings.
	*/
	template< typename... TStrings >
	struct StringCombiner;

	/// @brief	Specialization of string combiner with single string.
	template< char... CHARS >
	struct StringCombiner< StaticString<CHARS...> >
	{
		using String = StaticString<CHARS...>;
	};

	/// @brief	Specialization of string combiner with two strings.
	template< char... LEFT_CHARS, char... RIGHT_CARS >
	struct StringCombiner< StaticString<LEFT_CHARS...>, StaticString<RIGHT_CARS...> >
	{
		using String = StaticString<LEFT_CHARS..., RIGHT_CARS...>;
	};

	/// @brief	Specialization of string combiner with chain of strings.
	template< char... CHARS, typename... TStrings >
	struct StringCombiner< StaticString<CHARS...>, TStrings... >
	{
		using String = typename StringCombiner< StaticString<CHARS...>, typename StringCombiner<TStrings...>::String >::String;
	};
};

	/**
		@brief	Combiner of static strings.
		It is much useful for producing single static string from collection of ones.
		@tparam	TStrings	Collection of static strings to be combined into single one.
	*/
	template< typename... TStrings >
	using CombinedStaticString = typename utils::StringCombiner<TStrings...>::String;
};

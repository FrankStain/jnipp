// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Utils
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

	/// @brief	Static string trimming tool. Trims the right side of string.
	template< size_t NUMBER, bool IS_ENDED, typename TStoredString, char... CHARS >
	struct StringRightStripper;

	template< char... REST_CHARS, char... STORED_CHARS >
	struct StringRightStripper<0, true, StaticString<STORED_CHARS...>, REST_CHARS...>
	{
		using String = StaticString<STORED_CHARS...>;
	};

	template< size_t NUMBER, char CURRENT_CHAR, char... REST_CHARS, char... STORED_CHARS >
	struct StringRightStripper<NUMBER, false, StaticString<STORED_CHARS...>, CURRENT_CHAR, REST_CHARS...>
		: StringRightStripper<NUMBER - 1, NUMBER == 1, StaticString<STORED_CHARS..., CURRENT_CHAR>, REST_CHARS...>
	{

	};

	/// @brief	Class path extractor from `ClassName` and `ArrayName` static strings.
	template< typename TClassPathString >
	struct ClassPathExtractor;

	template< char... CHARS >
	struct ClassPathExtractor< StaticString<'L', CHARS...> >
	{
		using String = typename StringRightStripper<sizeof...( CHARS ) - 1, sizeof...( CHARS ) == 1, StaticString<>, CHARS...>::String;
	};

	template< char... CHARS >
	struct ClassPathExtractor< StaticString<'[', CHARS...> >
	{
		using String = StaticString<'[', CHARS...>;
	};
}

	/**
		@brief	Combiner of static strings.
		It is much useful for producing single static string from collection of ones.
		@tparam	TStrings	Collection of static strings to be combined into single one.
	*/
	template< typename... TStrings >
	using CombinedStaticString = typename Utils::StringCombiner<TStrings...>::String;

	/// @brief	Helper for producing valid name of Java class.
	template< char... CHARS >
	using ClassName = CombinedStaticString< StaticString<'L'>, StaticString<CHARS...>, StaticString<';'> >;

	/// @brief	Helper for producing valid name of Java array.
	template< typename TElementNameString >
	using ArrayName = CombinedStaticString< StaticString<'['>, TElementNameString >;

	/// @brief	Helper for producing valid name of Java function.
	template< typename TReturnTypeName, typename... TArgumentTypeNames >
	using FunctionSignature = CombinedStaticString< StaticString<'('>, TArgumentTypeNames..., StaticString<')'>, TReturnTypeName >;

	/// @brief	Class path extractor from `ClassName` and `ArrayName` static strings.
	template< typename TClassNameString >
	using ClassPath = typename Utils::ClassPathExtractor<TClassNameString>::String;
}

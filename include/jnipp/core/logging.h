// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


// "printf format" diagnostic irrelevant for next functions.
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"


namespace Jni
{
namespace Logging
{
	constexpr static const char TAG[] = "Jni++";

	/**
		@brief	Write arbitrary message into android log-cat.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@tparam	TArgumentTypes	Parameter pack of types of message arguments.
		@param	message_type	Type of message. `ANDROID_LOG_*` values allowed.
		@param	format			Message format.
		@param	arguments		List of message arguments to be formated. Only plain types allowed.
	*/
	template< typename... TArgumentTypes >
	inline void Message( const int32_t message_type, const char* format, TArgumentTypes... arguments )
	{
		#if( JNIPP_LOGS_ENABLED || JNIPP_DEBUG_BUILD )
		__android_log_print( message_type, TAG, format, std::forward<TArgumentTypes>( arguments )... );
		#endif
	}

	/**
		@brief	Write message into android log-cat with `VERBOSE` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@tparam	TArgumentTypes	Parameter pack of types of message arguments.
		@param	format			Message format.
		@param	arguments		List of message arguments to be formated. Only plain types allowed.
	*/
	template< typename... TArgumentTypes >
	inline void Verbose( const char* format, TArgumentTypes... arguments )
	{
		#if( ( JNIPP_LOGS_ENABLED || JNIPP_DEBUG_BUILD ) && JNIPP_LOGS_VERBOSE_ENABLED )
		__android_log_print( ANDROID_LOG_VERBOSE, TAG, format, std::forward<TArgumentTypes>( arguments )... );
		#endif
	}

	/**
		@brief	Write message into android log-cat with `DEBUG` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@tparam	TArgumentTypes	Parameter pack of types of message arguments.
		@param	format			Message format.
		@param	arguments		List of message arguments to be formated. Only plain types allowed.
	*/
	template< typename... TArgumentTypes >
	inline void Debug( const char* format, TArgumentTypes... arguments )
	{
		#if( ( JNIPP_LOGS_ENABLED || JNIPP_DEBUG_BUILD ) && JNIPP_LOGS_DEBUG_ENABLED )
		__android_log_print( ANDROID_LOG_DEBUG, TAG, format, std::forward<TArgumentTypes>( arguments )... );
		#endif
	}

	/**
		@brief	Write message into android log-cat with `INFO` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@tparam	TArgumentTypes	Parameter pack of types of message arguments.
		@param	format			Message format.
		@param	arguments		List of message arguments to be formated. Only plain types allowed.
	*/
	template< typename... TArgumentTypes >
	inline void Info( const char* format, TArgumentTypes... arguments )
	{
		#if( ( JNIPP_LOGS_ENABLED || JNIPP_DEBUG_BUILD ) && JNIPP_LOGS_INFO_ENABLED )
		__android_log_print( ANDROID_LOG_INFO, TAG, format, std::forward<TArgumentTypes>( arguments )... );
		#endif
	}

	/**
		@brief	Write message into android log-cat with `WARNING` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@tparam	TArgumentTypes	Parameter pack of types of message arguments.
		@param	format			Message format.
		@param	arguments		List of message arguments to be formated. Only plain types allowed.
	*/
	template< typename... TArgumentTypes >
	inline void Warning( const char* format, TArgumentTypes... arguments )
	{
		#if( ( JNIPP_LOGS_ENABLED || JNIPP_DEBUG_BUILD ) && JNIPP_LOGS_WARNING_ENABLED )
		__android_log_print( ANDROID_LOG_WARN, TAG, format, std::forward<TArgumentTypes>( arguments )... );
		#endif
	}

	/**
		@brief	Write message into android log-cat with `ERROR` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@tparam	TArgumentTypes	Parameter pack of types of message arguments.
		@param	format			Message format.
		@param	arguments		List of message arguments to be formated. Only plain types allowed.
	*/
	template< typename... TArgumentTypes >
	inline void Error( const char* format, TArgumentTypes... arguments )
	{
		#if( ( JNIPP_LOGS_ENABLED || JNIPP_DEBUG_BUILD ) && JNIPP_LOGS_EROR_ENABLED )
		__android_log_print( ANDROID_LOG_ERROR, TAG, format, std::forward<TArgumentTypes>( arguments )... );
		#endif
	}

	/**
		@brief	Write message into android log-cat with `ASSERT` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@tparam	TArgumentTypes	Parameter pack of types of message arguments.
		@param	format			Message format.
		@param	arguments		List of message arguments to be formated. Only plain types allowed.
	*/
	template< typename... TArgumentTypes >
	inline void Assert( const char* format, TArgumentTypes... arguments )
	{
		#if( ( JNIPP_LOGS_ENABLED || JNIPP_DEBUG_BUILD ) && JNIPP_LOGS_ASSERT_ENABLED )
		__android_log_print( ANDROID_LOG_FATAL, TAG, format, std::forward<TArgumentTypes>( arguments )... );
		#endif
	}
}
}

#pragma GCC diagnostic pop

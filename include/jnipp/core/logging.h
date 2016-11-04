// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
namespace logging
{
	constexpr static const char TAG[] = "Jni++";
	
	/**
		@brief	Write arbitrary message into android log-cat.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@param	message_type	Type of message. `ANDROID_LOG_*` values allowed.
		@param	format			Format of message.
		@param	...				Arguments of message to be formated. Only plain types allowed.
	*/
	inline void Message( const int32_t message_type, const char* format, ... )
	{
		#if( ( defined( JNIPP_LOGS_ENABLED ) and JNIPP_LOGS_ENABLED ) || JNIPP_DEBUG_BUILD )
		va_list arguments;
		va_start( arguments, format );
		__android_log_vprint( message_type, TAG, format, arguments );
		va_end( arguments );
		#endif
	};

	/**
		@brief	Write message into android log-cat with `VERBOSE` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@param	format			Format of message.
		@param	...				Arguments of message to be formated. Only plain types allowed.
	*/
	inline void Verbose( const char* format, ... )
	{
		#if( ( defined( JNIPP_LOGS_ENABLED ) and JNIPP_LOGS_ENABLED ) || JNIPP_DEBUG_BUILD )
		va_list arguments;
		va_start( arguments, format );
		__android_log_vprint( ANDROID_LOG_VERBOSE, TAG, format, arguments );
		va_end( arguments );
		#endif
	};

	/**
		@brief	Write message into android log-cat with `DEBUG` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@param	format			Format of message.
		@param	...				Arguments of message to be formated. Only plain types allowed.
	*/
	inline void Debug( const char* format, ... )
	{
		#if( ( defined( JNIPP_LOGS_ENABLED ) and JNIPP_LOGS_ENABLED ) || JNIPP_DEBUG_BUILD )
		va_list arguments;
		va_start( arguments, format );
		__android_log_vprint( ANDROID_LOG_DEBUG, TAG, format, arguments );
		va_end( arguments );
		#endif
	};

	/**
		@brief	Write message into android log-cat with `INFO` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@param	format			Format of message.
		@param	...				Arguments of message to be formated. Only plain types allowed.
	*/
	inline void Info( const char* format, ... )
	{
		#if( ( defined( JNIPP_LOGS_ENABLED ) and JNIPP_LOGS_ENABLED ) || JNIPP_DEBUG_BUILD )
		va_list arguments;
		va_start( arguments, format );
		__android_log_vprint( ANDROID_LOG_INFO, TAG, format, arguments );
		va_end( arguments );
		#endif
	};

	/**
		@brief	Write message into android log-cat with `WARNING` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@param	format			Format of message.
		@param	...				Arguments of message to be formated. Only plain types allowed.
	*/
	inline void Warning( const char* format, ... )
	{
		#if( ( defined( JNIPP_LOGS_ENABLED ) and JNIPP_LOGS_ENABLED ) || JNIPP_DEBUG_BUILD )
		va_list arguments;
		va_start( arguments, format );
		__android_log_vprint( ANDROID_LOG_WARN, TAG, format, arguments );
		va_end( arguments );
		#endif
	};

	/**
		@brief	Write message into android log-cat with `ERROR` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@param	format			Format of message.
		@param	...				Arguments of message to be formated. Only plain types allowed.
	*/
	inline void Error( const char* format, ... )
	{
		#if( ( defined( JNIPP_LOGS_ENABLED ) and JNIPP_LOGS_ENABLED ) || JNIPP_DEBUG_BUILD )
		va_list arguments;
		va_start( arguments, format );
		__android_log_vprint( ANDROID_LOG_ERROR, TAG, format, arguments );
		va_end( arguments );
		#endif
	};

	/**
		@brief	Write message into android log-cat with `ASSERT` type.
		@note	This function makes stuff only in debug build or if `JNIPP_LOGS_ENABLED` is set to `1`.
		@param	format			Format of message.
		@param	...				Arguments of message to be formated. Only plain types allowed.
	*/
	inline void Assert( const char* format, ... )
	{
		#if( ( defined( JNIPP_LOGS_ENABLED ) and JNIPP_LOGS_ENABLED ) || JNIPP_DEBUG_BUILD )
		va_list arguments;
		va_start( arguments, format );
		__android_log_vprint( ANDROID_LOG_FATAL, TAG, format, arguments );
		va_end( arguments );
		#endif
	};
};
};

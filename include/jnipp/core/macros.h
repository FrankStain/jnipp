// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Conditional return (c-ret) for shorter the service code.
#if( !defined( CRET ) )
	#define CRET( CONDITION, ... )				if( CONDITION ) { return __VA_ARGS__; }
#endif

#if( !defined( CRET_D ) )
	#define CRET_D( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Debug( __VA_ARGS__ ); return RESULT; }
#endif

#if( !defined( CRET_I ) )
	#define CRET_I( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Info( __VA_ARGS__ ); return RESULT; }
#endif

#if( !defined( CRET_W ) )
	#define CRET_W( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Warning( __VA_ARGS__ ); return RESULT; }
#endif

#if( !defined( CRET_E ) )
	#define CRET_E( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Error( __VA_ARGS__ ); return RESULT; }
#endif


/// @brief	Conditional continuation (c-con) for shorter the service code.
#if( !defined( CCON ) )
	#define CCON( CONDITION )					if( CONDITION ) { continue; }
#endif

#if( !defined( CCON_D ) )
	#define CCON_D( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Debug( __VA_ARGS__ ); continue; }
#endif

#if( !defined( CCON_I ) )
	#define CCON_I( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Info( __VA_ARGS__ ); continue; }
#endif

#if( !defined( CCON_W ) )
	#define CCON_W( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Warning( __VA_ARGS__ ); continue; }
#endif

#if( !defined( CCON_E ) )
	#define CCON_E( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Error( __VA_ARGS__ ); continue; }
#endif


/// @brief	Conditional break (c-brk) for shorter the service code.
#if( !defined( CBRK ) )
	#define CBRK( CONDITION )					if( CONDITION ) { break; }
#endif

#if( !defined( CBRK_D ) )
	#define CBRK_D( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Debug( __VA_ARGS__ ); break; }
#endif

#if( !defined( CBRK_I ) )
	#define CBRK_I( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Info( __VA_ARGS__ ); break; }
#endif

#if( !defined( CBRK_W ) )
	#define CBRK_W( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Warning( __VA_ARGS__ ); break; }
#endif

#if( !defined( CBRK_E ) )
	#define CBRK_E( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Error( __VA_ARGS__ ); break; }
#endif


#if( !defined( JNIPP_STRINGIFY ) )
	#define JNIPP_TO_STRING( EXPRESSION )	#EXPRESSION
	#define JNIPP_STRINGIFY( EXPRESSION )	JNIPP_TO_STRING( EXPRESSION )
#endif


/// @brief	Expectation macro.
#if( !defined( Expects ) )
	#define Expects( ... )										\
	if( !( __VA_ARGS__ ) )										\
	{															\
		JNIPP_LOG_ERROR(										\
			"%s:%d - Unexpected result of `%s` expression.",		\
			__FILE__, __LINE__, JNIPP_STRINGIFY( __VA_ARGS__ )	\
		);														\
		std::terminate();										\
	};
#endif


// @brief	Ensuring macro.
#if( !defined( Ensures ) )
	#define Ensures( ... )										\
	if( !( __VA_ARGS__ ) )										\
	{															\
		JNIPP_LOG_ERROR(										\
			"%s:%d - Unexpected result of `%s` expression.",		\
			__FILE__, __LINE__, JNIPP_STRINGIFY( __VA_ARGS__ )	\
		);														\
		std::terminate();										\
	};
#endif

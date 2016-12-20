// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Conditional return (c-ret) for shorter the service code.
#if( !defined( JNI_RETURN_IF ) )
	#define JNI_RETURN_IF( CONDITION, ... )				if( CONDITION ) { return __VA_ARGS__; }
#endif

#if( !defined( JNI_RETURN_IF_V ) )
	#define JNI_RETURN_IF_V( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Verbose( __VA_ARGS__ ); return RESULT; }
#endif

#if( !defined( JNI_RETURN_IF_D ) )
	#define JNI_RETURN_IF_D( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Debug( __VA_ARGS__ ); return RESULT; }
#endif

#if( !defined( JNI_RETURN_IF_I ) )
	#define JNI_RETURN_IF_I( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Info( __VA_ARGS__ ); return RESULT; }
#endif

#if( !defined( JNI_RETURN_IF_W ) )
	#define JNI_RETURN_IF_W( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Warning( __VA_ARGS__ ); return RESULT; }
#endif

#if( !defined( JNI_RETURN_IF_E ) )
	#define JNI_RETURN_IF_E( CONDITION, RESULT, ... )	if( CONDITION ) { jnipp::logging::Error( __VA_ARGS__ ); return RESULT; }
#endif


/// @brief	Conditional continuation (c-con) for shorter the service code.
#if( !defined( JNI_CONTINUE_IF ) )
	#define JNI_CONTINUE_IF( CONDITION )				if( CONDITION ) { continue; }
#endif

#if( !defined( JNI_CONTINUE_IF_V ) )
	#define JNI_CONTINUE_IF_V( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Verbose( __VA_ARGS__ ); continue; }
#endif

#if( !defined( JNI_CONTINUE_IF_D ) )
	#define JNI_CONTINUE_IF_D( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Debug( __VA_ARGS__ ); continue; }
#endif

#if( !defined( JNI_CONTINUE_IF_I ) )
	#define JNI_CONTINUE_IF_I( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Info( __VA_ARGS__ ); continue; }
#endif

#if( !defined( JNI_CONTINUE_IF_W ) )
	#define JNI_CONTINUE_IF_W( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Warning( __VA_ARGS__ ); continue; }
#endif

#if( !defined( JNI_CONTINUE_IF_E ) )
	#define JNI_CONTINUE_IF_E( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Error( __VA_ARGS__ ); continue; }
#endif


/// @brief	Conditional break (c-brk) for shorter the service code.
#if( !defined( JNI_BREAK_IF ) )
	#define JNI_BREAK_IF( CONDITION )					if( CONDITION ) { break; }
#endif

#if( !defined( JNI_BREAK_IF_V ) )
	#define JNI_BREAK_IF_V( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Verbose( __VA_ARGS__ ); break; }
#endif

#if( !defined( JNI_BREAK_IF_D ) )
	#define JNI_BREAK_IF_D( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Debug( __VA_ARGS__ ); break; }
#endif

#if( !defined( JNI_BREAK_IF_I ) )
	#define JNI_BREAK_IF_I( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Info( __VA_ARGS__ ); break; }
#endif

#if( !defined( JNI_BREAK_IF_W ) )
	#define JNI_BREAK_IF_W( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Warning( __VA_ARGS__ ); break; }
#endif

#if( !defined( JNI_BREAK_IF_E ) )
	#define JNI_BREAK_IF_E( CONDITION, ... )			if( CONDITION ) { jnipp::logging::Error( __VA_ARGS__ ); break; }
#endif


#if( !defined( JNI_STRINGIFY ) )
	#define JNI_PROMOTE_STRING( EXPRESSION )	#EXPRESSION
	#define JNI_STRINGIFY( EXPRESSION )			JNI_PROMOTE_STRING( EXPRESSION )
#endif


/// @brief	Expectation macro.
#if( !defined( JNI_EXPECTS ) )
	#define JNI_EXPECTS( ... )									\
	if( !( __VA_ARGS__ ) )										\
	{															\
		jnipp::logging::Assert(									\
			"%s:%d - Unexpected result of `%s` expression.",	\
			__FILE__, __LINE__, JNI_STRINGIFY( __VA_ARGS__ )	\
		);														\
		std::terminate();										\
	}
#endif


// @brief	Ensuring macro.
#if( !defined( JNI_ENSURES ) )
	#define JNI_ENSURES( ... )									\
	if( !( __VA_ARGS__ ) )										\
	{															\
		jnipp::logging::Assert(									\
			"%s:%d - Insurance failed due to "					\
			"unexpected result of `%s` expression.",			\
			__FILE__, __LINE__, JNI_STRINGIFY( __VA_ARGS__ )	\
		);														\
		std::terminate();										\
	}
#endif

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#include <jnipp/jnipp.h>

#if( JNIPP_LOG_HANDLES && JNIPP_LOG_CLASS_HANDLE )
	#define LOGV( ... )	jnipp::logging::Verbose( __VA_ARGS__ )
	#define LOGD( ... )	jnipp::logging::Debug( __VA_ARGS__ )
	#define LOGI( ... )	jnipp::logging::Info( __VA_ARGS__ )
	#define LOGW( ... )	jnipp::logging::Warning( __VA_ARGS__ )
	#define LOGE( ... )	jnipp::logging::Error( __VA_ARGS__ )
#else
	#define LOGV( ... )
	#define LOGD( ... )
	#define LOGI( ... )
	#define LOGW( ... )
	#define LOGE( ... )
#endif

#if( JNIPP_TRACING_ENABLED )
	#define LOG_PASS()	LOGV( "%s - Pass at %d.", __func__, __LINE__ )
	#define LOG_ENTER()	LOGV( "%s - Enter at %d.", __func__, __LINE__ )
	#define LOG_EXIT()	LOGV( "%s - Exit at %d.", __func__, __LINE__ )
	#define LOG_EXITW()	LOGW( "%s - Exit at %d.", __func__, __LINE__ )
	#define LOG_EXITE()	LOGE( "%s - Exit at %d.", __func__, __LINE__ )
#else
	#define LOG_ENTER( ... )
	#define LOG_EXIT( ... )
	#define LOG_EXITW( ... )
	#define LOG_EXITE( ... )
#endif


namespace jnipp
{
	ClassHandle::ClassHandle( const ClassHandle& other )
		: m_class( other.m_class )
	{
		LOG_PASS();
	};

	ClassHandle::ClassHandle( ClassHandle&& other )
		: m_class( std::move( other.m_class ) )
	{
		LOG_PASS();
	};

	ClassHandle::ClassHandle( const std::string& class_name )
		: ClassHandle( class_name.c_str() )
	{
		LOG_PASS();
	};

	ClassHandle::ClassHandle( const char* class_name )
	{
		LOG_ENTER();
		AcquireHandle( class_name );
		LOG_EXIT();
	};

	void ClassHandle::Invalidate()
	{
		LOG_ENTER();
		m_class.reset();
		LOG_EXIT();
	};

	void ClassHandle::AcquireHandle( const char* class_name )
	{
		LOG_ENTER();
		Invalidate();
		
		Expects( class_name != nullptr );
		Expects( strlen( class_name ) > 0 );

		m_class = VirtualMachine::GetClass( class_name );

		Ensures( IsValid() );
		LOG_EXIT();
	};

	void ClassHandle::AcquireHandle( jobject java_object )
	{
		LOG_ENTER();
		Invalidate();
		
		CRET( java_object == nullptr );
		m_class = VirtualMachine::GetClass( java_object );

		Ensures( IsValid() );
		LOG_EXIT();
	};

	const ClassHandle& ClassHandle::operator=( const ClassHandle& other )
	{
		LOG_ENTER();
		m_class = other.m_class;
		LOG_EXIT();
		return *this;
	};

	const ClassHandle& ClassHandle::operator=( ClassHandle&& other )
	{
		LOG_ENTER();
		m_class = std::move( other.m_class );
		LOG_EXIT();
		return *this;
	};

	const ClassHandle& ClassHandle::operator=( const std::string& class_name )
	{
		LOG_ENTER();
		AcquireHandle( class_name.c_str() );
		LOG_EXIT();
		return *this;
	};

	const ClassHandle& ClassHandle::operator=( const char* class_name )
	{
		LOG_ENTER();
		AcquireHandle( class_name );
		LOG_EXIT();
		return *this;
	};
};

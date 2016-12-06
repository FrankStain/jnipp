// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#include <jnipp/jnipp.h>

#if( JNIPP_LOG_HANDLES && JNIPP_LOG_OBJECT_HANDLE )
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
	ObjectHandle::ObjectHandle( jobject object_ref )
	{
		LOG_ENTER();
		AcquireObjectRef( object_ref );
		LOG_EXIT();
	};

	ObjectHandle::ObjectHandle( const ClassHandle& class_handle )
		: m_object_ref( class_handle.m_class_ref )
	{
		LOG_PASS();
	};

	ObjectHandle::ObjectHandle( ClassHandle&& class_handle )
		: m_object_ref( std::move( class_handle.m_class_ref ) )
	{
		LOG_PASS();
	};

	ObjectHandle::ObjectHandle( const ObjectHandle& other )
		: m_object_ref( other.m_object_ref )
		, m_class_handle( other.m_class_handle )
	{
		LOG_PASS();
	};

	ObjectHandle::ObjectHandle( ObjectHandle&& other )
		: m_object_ref( std::move( other.m_object_ref ) )
		, m_class_handle( std::move( other.m_class_handle ) )
	{
		LOG_PASS();
	};

	void ObjectHandle::Invalidate()
	{
		LOG_ENTER();
		m_object_ref.reset();
		m_class_handle.Invalidate();
		LOG_EXIT();
	};

	const ObjectHandle& ObjectHandle::operator=( jobject object_ref )
	{
		LOG_ENTER();
		AcquireObjectRef( object_ref );
		LOG_EXIT();
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( const ClassHandle& class_handle )
	{
		LOG_ENTER();
		m_object_ref	= class_handle.m_class_ref;
		m_class_handle.Invalidate();
		LOG_EXIT();
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( ClassHandle&& class_handle )
	{
		LOG_ENTER();
		m_object_ref	= std::move( class_handle.m_class_ref );
		m_class_handle.Invalidate();
		LOG_EXIT();
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( const ObjectHandle& other )
	{
		LOG_ENTER();
		m_object_ref	= other.m_object_ref;
		m_class_handle.Invalidate();
		LOG_EXIT();
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( ObjectHandle&& other )
	{
		LOG_ENTER();
		m_object_ref	= std::move( other.m_object_ref );
		m_class_handle.Invalidate();
		LOG_EXIT();
		return *this;
	};

	void ObjectHandle::DeleteObjectRef( jobject object_ref )
	{
		LOG_ENTER();
		CRET_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		VirtualMachine::GetLocalEnvironment()->DeleteGlobalRef( object_ref );
		LOG_EXIT();
	};

	void ObjectHandle::InitClassHandle() const
	{
		LOG_ENTER();
		CRET( !m_object_ref || m_class_handle.IsValid() );
		m_class_handle.AcquireHandle( m_object_ref.get() );
		LOG_EXIT();
	};

	void ObjectHandle::AcquireObjectRef( jobject object_ref )
	{
		LOG_ENTER();
		CRET_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		CRET_W( object_ref == nullptr, , "Attempt to get global ref of null object." );

		m_object_ref = { VirtualMachine::GetLocalEnvironment()->NewGlobalRef( object_ref ), ObjectHandle::DeleteObjectRef };
		m_class_handle.Invalidate();
		LOG_EXIT();
	};
};

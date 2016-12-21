// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#include <jnipp/jnipp.h>


namespace Jni
{
	ObjectHandle::ObjectHandle( jobject object_ref )
	{
		AcquireObjectRef( object_ref );
	};

	ObjectHandle::ObjectHandle( const Class& class_handle )
		: m_object_ref( class_handle.m_class_ref )
	{

	};

	ObjectHandle::ObjectHandle( Class&& class_handle )
		: m_object_ref( std::move( class_handle.m_class_ref ) )
	{

	};

	ObjectHandle::ObjectHandle( const ObjectHandle& other )
		: m_object_ref( other.m_object_ref )
		, m_class_handle( other.m_class_handle )
	{

	};

	ObjectHandle::ObjectHandle( ObjectHandle&& other )
		: m_object_ref( std::move( other.m_object_ref ) )
		, m_class_handle( std::move( other.m_class_handle ) )
	{

	};

	void ObjectHandle::Invalidate()
	{
		m_object_ref.reset();
		m_class_handle.Invalidate();
	};

	const ObjectHandle& ObjectHandle::operator=( jobject object_ref )
	{
		AcquireObjectRef( object_ref );
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( const Class& class_handle )
	{
		m_object_ref	= class_handle.m_class_ref;
		m_class_handle.Invalidate();
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( Class&& class_handle )
	{
		m_object_ref	= std::move( class_handle.m_class_ref );
		m_class_handle.Invalidate();
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( const ObjectHandle& other )
	{
		m_object_ref	= other.m_object_ref;
		m_class_handle.Invalidate();
		return *this;
	};

	const ObjectHandle& ObjectHandle::operator=( ObjectHandle&& other )
	{
		m_object_ref	= std::move( other.m_object_ref );
		m_class_handle.Invalidate();
		return *this;
	};

	void ObjectHandle::DeleteObjectRef( jobject object_ref )
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		VirtualMachine::GetLocalEnvironment()->DeleteGlobalRef( object_ref );
	};

	void ObjectHandle::InitClassHandle() const
	{
		JNI_RETURN_IF( !m_object_ref || m_class_handle.IsValid() );
		m_class_handle.AcquireHandle( m_object_ref.get() );
	};

	void ObjectHandle::AcquireObjectRef( jobject object_ref )
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		JNI_RETURN_IF_W( object_ref == nullptr, , "Attempt to get global ref of null object." );

		m_object_ref = { VirtualMachine::GetLocalEnvironment()->NewGlobalRef( object_ref ), ObjectHandle::DeleteObjectRef };
		m_class_handle.Invalidate();
	};
};

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#include <jnipp/jnipp.h>


namespace Jni
{
	Object::Object( jobject object_ref )
	{
		AcquireObjectRef( object_ref );
	}

	Object::Object( const Class& class_handle )
		: m_object_ref( class_handle.m_class_ref )
	{

	}

	Object::Object( Class&& class_handle )
		: m_object_ref( std::move( class_handle.m_class_ref ) )
	{

	}

	Object::Object( const Object& other )
		: m_object_ref( other.m_object_ref )
		, m_class_handle( other.m_class_handle )
	{

	}

	Object::Object( Object&& other )
		: m_object_ref( std::move( other.m_object_ref ) )
		, m_class_handle( std::move( other.m_class_handle ) )
	{

	}

	void Object::Invalidate()
	{
		m_object_ref.reset();
		m_class_handle.Invalidate();
	}

	const bool Object::IsInstanceOf( const Class& base_class ) const
	{
		JNI_RETURN_IF( !IsValid() || !base_class, false );
		return VirtualMachine::GetLocalEnvironment()->IsInstanceOf( m_object_ref.get(), *base_class );
	}

	const Object& Object::operator=( jobject object_ref )
	{
		AcquireObjectRef( object_ref );
		return *this;
	}

	const Object& Object::operator=( const Class& class_handle )
	{
		m_object_ref	= class_handle.m_class_ref;
		m_class_handle.Invalidate();
		return *this;
	}

	const Object& Object::operator=( Class&& class_handle )
	{
		m_object_ref	= std::move( class_handle.m_class_ref );
		m_class_handle.Invalidate();
		return *this;
	}

	const Object& Object::operator=( const Object& other )
	{
		m_object_ref	= other.m_object_ref;
		m_class_handle.Invalidate();
		return *this;
	}

	const Object& Object::operator=( Object&& other )
	{
		m_object_ref	= std::move( other.m_object_ref );
		m_class_handle.Invalidate();
		return *this;
	}

	void Object::DeleteObjectRef( jobject object_ref )
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		VirtualMachine::GetLocalEnvironment()->DeleteGlobalRef( object_ref );
	}

	void Object::RetrieveClass() const
	{
		JNI_RETURN_IF( !m_object_ref || m_class_handle.IsValid() );
		m_class_handle.AcquireClassReference( m_object_ref.get() );
	}

	void Object::AcquireObjectRef( jobject object_ref )
	{
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), , "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );
		JNI_RETURN_IF_W( object_ref == nullptr, , "Attempt to get global ref of null object." );

		m_object_ref = { VirtualMachine::GetLocalEnvironment()->NewGlobalRef( object_ref ), Object::DeleteObjectRef };
		m_class_handle.Invalidate();
	}

	const bool operator==( const Object& left, const Object& right )
	{
		return VirtualMachine::GetLocalEnvironment()->IsSameObject( *left, *right );
	}

	const bool operator!=( const Object& left, const Object& right )
	{
		return !VirtualMachine::GetLocalEnvironment()->IsSameObject( *left, *right );
	}
}

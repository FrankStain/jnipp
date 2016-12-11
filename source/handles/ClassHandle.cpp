// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#include <jnipp/jnipp.h>


namespace jnipp
{
	ClassHandle::ClassHandle( const ClassHandle& other )
		: m_class_ref( other.m_class_ref )
	{

	};

	ClassHandle::ClassHandle( ClassHandle&& other )
		: m_class_ref( std::move( other.m_class_ref ) )
	{

	};

	ClassHandle::ClassHandle( const std::string& class_name )
		: ClassHandle( class_name.c_str() )
	{

	};

	ClassHandle::ClassHandle( const char* class_name )
	{
		AcquireHandle( class_name );
	};

	void ClassHandle::Invalidate()
	{
		m_class_ref.reset();
	};

	const std::string ClassHandle::GetCanonicalName() const
	{
		CRET( !IsValid(), {} );
		Expects( VirtualMachine::IsValid() );
		return VirtualMachine::GetInstance().m_get_canonical_name.Call( GetJniReference() );
	};

	const std::string ClassHandle::GetName() const
	{
		CRET( !IsValid(), {} );
		Expects( VirtualMachine::IsValid() );
		std::string class_name{ VirtualMachine::GetInstance().m_get_name.Call( GetJniReference() ) };

		for( char& stored_char : class_name )
		{
			if( stored_char == '.' )
			{
				stored_char = '/';
			};
		};

		return class_name;
	};

	const std::string ClassHandle::GetSimpleName() const
	{
		CRET( !IsValid(), {} );
		Expects( VirtualMachine::IsValid() );
		return VirtualMachine::GetInstance().m_get_simple_name.Call( GetJniReference() );
	};

	ClassHandle ClassHandle::GetParentClassHandle() const
	{
		CRET( !IsValid(), {} );
		Expects( VirtualMachine::IsValid() );
		return VirtualMachine::GetInstance().m_get_super_class_func.Call( GetJniReference() );
	};

	void ClassHandle::AcquireHandle( const char* class_name )
	{
		Invalidate();
		
		Expects( class_name != nullptr );
		Expects( strlen( class_name ) > 0 );

		m_class_ref = VirtualMachine::GetInstance().GetClass( class_name );

		Ensures( IsValid() );
	};

	void ClassHandle::AcquireHandle( jobject object_ref )
	{
		Invalidate();
		
		CRET( object_ref == nullptr );
		m_class_ref = VirtualMachine::GetInstance().GetClass( object_ref );

		Ensures( IsValid() );
	};

	const ClassHandle& ClassHandle::operator=( jclass class_ref )
	{
		m_class_ref = VirtualMachine::GetInstance().GetClass( class_ref );
		return *this;
	};

	const ClassHandle& ClassHandle::operator=( const ClassHandle& other )
	{
		m_class_ref = other.m_class_ref;
		return *this;
	};

	const ClassHandle& ClassHandle::operator=( ClassHandle&& other )
	{
		m_class_ref = std::move( other.m_class_ref );
		return *this;
	};

	const ClassHandle& ClassHandle::operator=( const std::string& class_name )
	{
		AcquireHandle( class_name.c_str() );
		return *this;
	};

	const ClassHandle& ClassHandle::operator=( const char* class_name )
	{
		AcquireHandle( class_name );
		return *this;
	};
};

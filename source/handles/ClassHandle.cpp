// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#include <jnipp/jnipp.h>


namespace Jni
{
	Class::Class( const Class& other )
		: m_class_ref( other.m_class_ref )
	{

	};

	Class::Class( Class&& other )
		: m_class_ref( std::move( other.m_class_ref ) )
	{

	};

	Class::Class( const std::string& class_name )
		: Class( class_name.c_str() )
	{

	};

	Class::Class( const char* class_name )
	{
		AcquireClassReference( class_name );
	};

	void Class::Invalidate()
	{
		m_class_ref.reset();
	};

	const std::string Class::GetCanonicalName() const
	{
		JNI_RETURN_IF( !IsValid(), {} );
		JNI_EXPECTS( VirtualMachine::IsValid() );
		return VirtualMachine::GetInstance().m_get_canonical_name.Call( GetJniReference() );
	};

	const std::string Class::GetName() const
	{
		JNI_RETURN_IF( !IsValid(), {} );
		JNI_EXPECTS( VirtualMachine::IsValid() );
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

	const std::string Class::GetSimpleName() const
	{
		JNI_RETURN_IF( !IsValid(), {} );
		JNI_EXPECTS( VirtualMachine::IsValid() );
		return VirtualMachine::GetInstance().m_get_simple_name.Call( GetJniReference() );
	};

	Class Class::GetParentClass() const
	{
		JNI_RETURN_IF( !IsValid(), {} );
		JNI_EXPECTS( VirtualMachine::IsValid() );
		return VirtualMachine::GetInstance().m_get_super_class_func.Call( GetJniReference() );
	};

	void Class::AcquireClassReference( const char* class_name )
	{
		Invalidate();
		
		JNI_EXPECTS( class_name != nullptr );
		JNI_EXPECTS( strlen( class_name ) > 0 );

		m_class_ref = VirtualMachine::GetInstance().GetClass( class_name );

		JNI_ENSURES( IsValid() );
	};

	void Class::AcquireClassReference( jobject object_ref )
	{
		Invalidate();
		
		JNI_RETURN_IF( object_ref == nullptr );
		m_class_ref = VirtualMachine::GetInstance().GetClass( object_ref );

		JNI_ENSURES( IsValid() );
	};

	const Class& Class::operator=( jclass class_ref )
	{
		m_class_ref = VirtualMachine::GetInstance().GetClass( class_ref );
		return *this;
	};

	const Class& Class::operator=( const Class& other )
	{
		m_class_ref = other.m_class_ref;
		return *this;
	};

	const Class& Class::operator=( Class&& other )
	{
		m_class_ref = std::move( other.m_class_ref );
		return *this;
	};

	const Class& Class::operator=( const std::string& class_name )
	{
		AcquireClassReference( class_name.c_str() );
		return *this;
	};

	const Class& Class::operator=( const char* class_name )
	{
		AcquireClassReference( class_name );
		return *this;
	};
};

#include <jnipp/jnipp.h>
#include <jnipp/android/Configuration.h>


namespace Jni
{
namespace Android
{
	Locale Configuration::GetLocale() const
	{
		JNI_RETURN_IF( m_handles->locale, m_handles->locale.GetValue( *this, {} ) );

		auto locales = m_handles->get_locales.Call( *this );
		JNI_RETURN_IF( locales.IsEmpty(), {} );

		return locales.GetLocale( 0 );
	}
}
}

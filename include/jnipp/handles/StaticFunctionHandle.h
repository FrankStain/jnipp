// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	class FunctionHandle final
	{
		friend class JniEnv;
	public:

	private:
		ClassHandle	m_class_handle;			// Handle to class owning the static method.
		jmethodID	m_function_id	= 0;	// Id of Java static method.
	};
};

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	class StaticFunctionHandle final
	{
		friend class JniEnv;
	public:
		StaticFunctionHandle() = delete;
		StaticFunctionHandle( const StaticFunctionHandle& other );
		StaticFunctionHandle( StaticFunctionHandle&& other );
		StaticFunctionHandle( const std::string& class_name, const std::string& function_name );
		StaticFunctionHandle( const ClassHandle& class_handle, const std::string& function_name );
		StaticFunctionHandle( const char* class_name, const char* function_name );
		StaticFunctionHandle( const ClassHandle& class_handle, const char* function_name );


		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_class_handle.IsValid() && ( m_function_id != 0 ); };

		/// @brief	Call the function with given arguments.
		inline TNativeReturnType Call( const ObjectHandle& object_handle, const TNativeArguments&... arguments ) const;


		inline explicit operator const bool () const	{ return IsValid(); };

	private:
		using Signature		= FunctionSignature<TNativeReturnType, TNativeArguments...>;
		using CallDecorator	= utils::StaticFunctionCall<TNativeReturnType, TNativeArguments...>;

		/// @brief	Call the function with given arguments.
		inline TNativeReturnType Call( JNIEnv* local_env, const TNativeArguments&... arguments ) const;

	private:
		ClassHandle	m_class_handle;			// Handle to class owning the static method.
		jmethodID	m_function_id	= 0;	// Id of Java static method.
	};
};

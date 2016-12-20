// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename TNativeReturnType, typename... TNativeArguments >
	class StaticFunctionHandle final
	{
		friend class JniEnv;
	public:
		StaticFunctionHandle() = default;
		StaticFunctionHandle( const StaticFunctionHandle& other );
		StaticFunctionHandle( StaticFunctionHandle&& other );
		StaticFunctionHandle( const std::string& class_name, const std::string& function_name );
		StaticFunctionHandle( const ClassHandle& class_handle, const std::string& function_name );
		StaticFunctionHandle( const char* class_name, const char* function_name );
		StaticFunctionHandle( const ClassHandle& class_handle, const char* function_name );


		/// @brief	Call the function with given arguments.
		inline TNativeReturnType Call( const TNativeArguments&... arguments ) const;


		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_class_handle.IsValid() && ( m_function_id != 0 ); };

		/// @brief	Get the JNI id of Java static method.
		inline jmethodID GetFunctionId() const			{ return m_function_id; };


		inline const StaticFunctionHandle& operator = ( const StaticFunctionHandle& other );
		inline const StaticFunctionHandle& operator = ( StaticFunctionHandle&& other );


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jmethodID operator * () const			{ return GetFunctionId(); };

	private:
		using Signature		= FunctionSignature< Marshaling::TypeSignature<TNativeReturnType>, Marshaling::TypeSignature<TNativeArguments>... >;
		using CallDecorator	= Utils::StaticFunctionCall<TNativeReturnType, TNativeArguments...>;

		/// @brief	Call the function with given arguments.
		inline TNativeReturnType Call( JNIEnv* local_env, const TNativeArguments&... arguments ) const;

	private:
		ClassHandle	m_class_handle;				// Handle to class owning the static method.
		jmethodID	m_function_id	= nullptr;	// Id of Java static method.
	};
};

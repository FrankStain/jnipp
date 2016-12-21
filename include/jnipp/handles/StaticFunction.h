// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/// @brief	Handle of arbitrary Java static function.
	template< typename TNativeReturnType, typename... TNativeArguments >
	class StaticFunction final
	{
		friend class JniEnv;
	public:
		StaticFunction() = default;
		StaticFunction( const StaticFunction& other );
		StaticFunction( StaticFunction&& other );
		StaticFunction( const std::string& class_name, const std::string& function_name );
		StaticFunction( const Class& class_handle, const std::string& function_name );
		StaticFunction( const char* class_name, const char* function_name );
		StaticFunction( const Class& class_handle, const char* function_name );


		/// @brief	Call the function with given arguments.
		inline TNativeReturnType Call( const TNativeArguments&... arguments ) const;


		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_class_handle.IsValid() && ( m_function_id != 0 ); };

		/// @brief	Get the JNI id of Java static method.
		inline jmethodID GetFunctionId() const			{ return m_function_id; };

		/// @brief	Get the function signature string.
		inline const char* GetSignature() const			{ return Signature::GetString(); };


		inline const StaticFunction& operator = ( const StaticFunction& other );
		inline const StaticFunction& operator = ( StaticFunction&& other );


		inline explicit operator const bool () const	{ return IsValid(); };
		inline jmethodID operator * () const			{ return GetFunctionId(); };

	private:
		using Signature		= FunctionSignature< Marshaling::TypeSignature<TNativeReturnType>, Marshaling::TypeSignature<TNativeArguments>... >;
		using CallDecorator	= Utils::StaticFunctionCall<TNativeReturnType, TNativeArguments...>;

		/// @brief	Call the function with given arguments.
		inline TNativeReturnType Call( JNIEnv* local_env, const TNativeArguments&... arguments ) const;

	private:
		Class		m_class_handle;				// Handle to class owning the static method.
		jmethodID	m_function_id	= nullptr;	// Id of Java static method.
	};
};

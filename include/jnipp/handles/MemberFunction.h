// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	/// @brief	Handle of arbitrary Java member function.
	template< typename TNativeReturnType, typename... TNativeArguments >
	class MemberFunction final
	{
		friend class Environment;
	public:
		MemberFunction() = default;
		MemberFunction( const MemberFunction& other );
		MemberFunction( MemberFunction&& other );
		MemberFunction( const std::string& class_name, const std::string& function_name );
		MemberFunction( const Class& class_handle, const std::string& function_name );
		MemberFunction( const char* class_name, const char* function_name );
		MemberFunction( const Class& class_handle, const char* function_name );


		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( const Object& object_handle, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( jobject object_ref, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual( const Object& object_handle, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual( jobject object_ref, const TNativeArguments&... arguments ) const;


		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const										{ return m_function_id != 0; };

		/// @brief	Get the JNI id of Java object method.
		inline jmethodID GetFunctionId() const									{ return m_function_id; };

		/// @brief	Get the function signature string.
		inline const char* GetSignature() const									{ return Signature::GetString(); };


		inline const MemberFunction& operator = ( const MemberFunction& other )	{ m_function_id = other.m_function_id; return *this; };
		inline const MemberFunction& operator = ( MemberFunction&& other )		{ m_function_id = std::move( other.m_function_id ); return *this; };


		inline explicit operator const bool () const							{ return IsValid(); };
		inline jmethodID operator * () const									{ return GetFunctionId(); };

	private:
		using Signature				= FunctionSignature< Marshaling::TypeSignature<TNativeReturnType>, Marshaling::TypeSignature<TNativeArguments>... >;
		using FunctionInvocation	= Utils::MemberFunctionInvocation<TNativeReturnType, TNativeArguments...>;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( JNIEnv* local_env, const Object& object_handle, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( JNIEnv* local_env, jobject object_ref, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual(
			JNIEnv* local_env,
			const Object& object_handle,
			const TNativeArguments&... arguments
		) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual(
			JNIEnv* local_env,
			jobject object_ref,
			const TNativeArguments&... arguments
		) const;

	private:
		Class		m_class_handle;				// Handle to class owning the static method.
		jmethodID	m_function_id	= nullptr;	// Id of Java object method.
	};
};

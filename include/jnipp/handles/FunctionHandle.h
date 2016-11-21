// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	/// @brief	Handle to member-function (method) of Java object.
	template< typename TNativeReturnType, typename... TNativeArguments >
	class FunctionHandle final
	{
		friend class JniEnv;
	public:
		FunctionHandle() = delete;
		FunctionHandle( const FunctionHandle& other );
		FunctionHandle( FunctionHandle&& other );
		FunctionHandle( const std::string& class_name, const std::string& function_name );
		FunctionHandle( const ClassHandle& class_handle, const std::string& function_name );
		FunctionHandle( const char* class_name, const char* function_name );
		FunctionHandle( const ClassHandle& class_handle, const char* function_name );


		/// @brief	Check the field handle carries valid value.
		inline const bool IsValid() const				{ return m_function_id != 0; };

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( const ObjectHandle& object_handle, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( jobject object_ref, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual( const ObjectHandle& object_handle, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual( jobject object_ref, const TNativeArguments&... arguments ) const;


		inline explicit operator const bool () const	{ return IsValid(); };

	private:
		using Signature		= FunctionSignature<TNativeReturnType, TNativeArguments...>;
		using CallDecorator	= utils::FunctionCall<TNativeReturnType, TNativeArguments...>;

		FunctionHandle( jclass class_ref, const char* function_name );

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( JNIEnv* local_env, const ObjectHandle& object_handle, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType Call( JNIEnv* local_env, jobject object_ref, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual( JNIEnv* local_env, const ObjectHandle& object_handle, const TNativeArguments&... arguments ) const;

		/// @brief	Call the function with given arguments for given Java object and return result.
		inline TNativeReturnType CallNonVirtual( JNIEnv* local_env, jobject object_ref, const TNativeArguments&... arguments ) const;

	private:
		jmethodID	m_function_id	= 0; // Id of Java object method.
	};
};

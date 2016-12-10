// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace jnipp
{
	/**
		@brief	Facade for native binding.
		@note	This type is designed to be brace-initialized.
	*/
	struct NativeFunction final
	{
		void*		address;	// Address of function.
		const char*	signature;	// Function signature.
		const char*	name;		// Function name.

		/**
			@brief	Generic constructor to automatically determinate the signature of given function.
			@tparam	TReturnType		Type of value returned by function. Only JNI interpretations accepted.
			@tparam	TSenderType		Type of JNI interpretation of Java object, which invokes the function. Only `jobject` and `jclass` may be accepted.
			@tparam	TArgumentTypes	Pack of function arguments. Only JNI interpretations accepted.
			@param	func_name		The name of given function for Java.
			@param	func_address	Actual address of function.
		*/
		template< typename TReturnType, typename TSenderType, typename... TArgumentTypes >
		NativeFunction( const char* func_name, TReturnType (*func_address)( JNIEnv*, TSenderType, TArgumentTypes... ) )
			: address( reinterpret_cast<void*>( func_address ) )
			, signature( FunctionSignature< marshaling::JavaTypeSignature<TReturnType>, marshaling::JavaTypeSignature<TArgumentTypes>... >::GetString() )
			, name( func_name )
		{
			static_assert(
				std::is_same<jobject, TSenderType>::value || std::is_same<jclass, TSenderType>::value,
				"The function handler must be `jobject` or `jclass`."
			);
		};

		/// @brief	Get JNI-consumable form of native function.
		inline JNINativeMethod GetJniNativeMethod() const
		{
			return { name, signature, address };
		};
	};

	/**
		@brief	Binding table for native handlers of Java classes.
		@note	This type is designed to be brace-initialized.
	*/
	struct NativeBindingTable final
	{
		const char*								class_name;	// Name of Java class.
		std::initializer_list<NativeFunction>	natives;	// List of native handlers.
	};
};

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
		std::string	signature;	// Function signature.
		std::string	name;		// Function name.

		template< typename TReturnType, typename... TArgumentTypes >
		NativeFunction( const char* func_name, TReturnType (*func_address)( TArgumentTypes... ) )
			: address( reinterpret_cast<void*>( func_address ) )
			, signature( FunctionSignature< marshaling::TypeSignature<TReturnType>, marshaling::TypeSignature<TArgumentTypes>... >::GetString() )
			, name( func_name )
		{

		};

		/// @brief	Get JNI-consumable form of native function.
		inline JNINativeMethod GetJniNativeMethod() const
		{
			return { name.c_str(), signature.c_str(), address };
		};
	};

	/**
		@brief	Binding table for native handlers of Java classes.
		@note	This type is designed to be brace-initialized.
	*/
	struct NativeBindingTable final
	{
		std::string								class_name;	// Name of Java class.
		std::initializer_list<NativeFunction>	natives;	// List of native handlers.
	};
};

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
		void*		address;
		std::string	signature;

		template< typename TReturnType, typename... TArgumentTypes >
		NativeFunction( TReturnType (*func_address)( TArgumentTypes... ) )
			: address( reinterpret_cast<void*>( func_address ) )
			, signature( FunctionSignature< TypeSignature<TReturnType>, TypeSignature<TArgumentTypes>... >::GetString() )
		{

		};
	};

	/**
		@brief	Binding table for native handlers of Java classes.
		@note	This type is designed to be brace-initialized.
	*/
	struct NativeBindingTable final
	{
		std::string								class_name;
		std::initializer_list<NativeFunction>	natives;
	};
};

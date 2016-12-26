// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Environment traits stores the pointers to `JNIEnv::*` functions, which may be used for given `TNativeType`.
	template< typename TNativeType >
	struct EnvironmentTraits
	{
		static_assert( !std::is_pointer<TNativeType>::value, "The native type may not be pointer." );
		static_assert( !std::is_reference<TNativeType>::value, "The native type may not be reference." );
		static_assert( !std::is_const<TNativeType>::value, "The native type may not be const." );
		static_assert( !std::is_volatile<TNativeType>::value, "The native type may not be volatile." );


		/// @brief	Pointer to member function of `JNIEnv` to read `object` member fields.
		static constexpr auto FIELD_READ_HANDLER			= &JNIEnv::GetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` member fields.
		static constexpr auto FIELD_WRITE_HANDLER			= &JNIEnv::SetObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to read `object` static fields.
		static constexpr auto STATIC_FIELD_READ_HANDLER		= &JNIEnv::GetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to write `object` static fields.
		static constexpr auto STATIC_FIELD_WRITE_HANDLER	= &JNIEnv::SetStaticObjectField;

		/// @brief	Pointer to member function of `JNIEnv` to call regular method.
		static constexpr auto FUNCTION_HANDLER				= &JNIEnv::CallObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call static method.
		static constexpr auto STATIC_FUNCTION_HANDLER		= &JNIEnv::CallStaticObjectMethod;

		/// @brief	Pointer to member function of `JNIEnv` to call non-virtual method.
		static constexpr auto NONVIRTUAL_FUNCTION_HANDLER	= &JNIEnv::CallNonvirtualObjectMethod;
	};
};
};

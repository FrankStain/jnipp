// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Simplifying macro to shortening the `NativeFunction` initialization and hiding the usage duplication.
#define JNI_NATIVE_HANDLER( NAME, FUNC )	Jni::Utils::NativeFunctionBuilder<decltype( FUNC )>::GetNativeFunction<FUNC>( NAME )

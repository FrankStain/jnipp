// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


#define JNI_NATIVE_HANDLER( NAME, FUNC )	Jni::Utils::NativeFunctionBuilder<decltype( FUNC )>::GetNativeFunction<FUNC>( NAME )

// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace Jni
{
/// @brief	Logging support for Jni++. Only android log-cat used here by default.
namespace Logging {};

/// @brief	Useful utils for Jni++.
namespace Utils {};

/// @brief	Type marshaling for Jni++.
namespace Marshaling {};
};


// Jni++ configuration.
#include <jnipp/core/configuration.h>

// Most major system includes.
#include <cstdint>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <memory>
#include <jni.h>
#include <android/log.h>

// Jni++ core stuff.
#include <jnipp/core/logging.h>
#include <jnipp/core/macros.h>

// Jni++ utils.
#include <jnipp/utils/StaticString.h>
#include <jnipp/utils/StaticString.operations.h>

// Jni++ type marshaling.
#include <jnipp/marshaling/NativeType.h>
#include <jnipp/marshaling/JavaType.h>
#include <jnipp/marshaling/TypeConvert.h>
#include <jnipp/marshaling/JniEnvFacade.h>

// Jni++ forward declarations.
#include <jnipp/utils/forwards.h>

// Jni++ wrap for Java classes.
#include <jnipp/handles/ClassHandle.h>
#include <jnipp/handles/ObjectHandle.h>
#include <jnipp/marshaling/ClassHandleConvert.h>
#include <jnipp/marshaling/ObjectHandleConvert.h>

// Jni++ wrap for Java class fields.
#include <jnipp/handles/FieldHandle.h>
#include <jnipp/handles/StaticFieldHandle.h>

// Jni++ wrap for Java functions.
#include <jnipp/utils/FunctionCall.h>
#include <jnipp/utils/StaticFunctionCall.h>
#include <jnipp/handles/FunctionHandle.h>
#include <jnipp/handles/StaticFunctionHandle.h>

// Some crucial Jni++ types.
#include <jnipp/utils/types.h>

// Jni++ major utility - virtual machine wrap.
#include <jnipp/utils/VirtualMachine.h>
#include <jnipp/utils/JniEnv.h>

// Deferred implementation of Jni++ functionality.
#include <jnipp/utils/JniEnv.inl>
#include <jnipp/marshaling/TypeConvert.FromJava.inl>
#include <jnipp/marshaling/TypeConvert.ToJava.inl>
#include <jnipp/utils/FunctionCall.inl>
#include <jnipp/utils/StaticFunctionCall.inl>
#include <jnipp/handles/ObjectHandle.inl>
#include <jnipp/handles/FieldHandle.inl>
#include <jnipp/handles/StaticFieldHandle.inl>
#include <jnipp/handles/FunctionHandle.inl>
#include <jnipp/handles/StaticFunctionHandle.inl>

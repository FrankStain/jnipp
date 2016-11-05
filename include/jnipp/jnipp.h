// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


/// @brief	Jni++ main namespace.
namespace jnipp
{
/// @brief	Logging support for Jni++. Only android log-cat used here by default.
namespace logging {};

/// @brief	Useful utils for Jni++.
namespace utils {};

/// @brief	Type marshaling for Jni++.
namespace marshaling {};
};


// Jni++ configuration.
#include <jnipp/core/configuration.h>

// Most major includes.
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

// Jni++ wrap for Java classes.
#include <jnipp/handles/ClassHandle.h>
#include <jnipp/handles/ObjectHandle.h>

// Jni++ wrap for Java class fields.
#include <jnipp/handles/FieldHandle.h>
#include <jnipp/handles/StaticFieldHandle.h>

// Jni++ major utility - virtual machine wrap.
#include <jnipp/core/types.h>
#include <jnipp/utils/VirtualMachine.h>
#include <jnipp/utils/JniEnv.h>

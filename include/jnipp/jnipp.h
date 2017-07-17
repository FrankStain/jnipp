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

/// @brief	Regular Java classes from Android SDK.
namespace Android {};
}


// Jni++ configuration.
#include "core/configuration.h"

// Most major system includes.
#include <cstdint>
#include <string>
#include <typeinfo>
#include <typeindex>
#include <vector>
#include <deque>
#include <list>
#include <set>
#include <map>
#include <unordered_map>
#include <algorithm>
#include <iterator>
#include <memory>
#include <jni.h>
#include <android/log.h>

// Jni++ core stuff.
#include "core/logging.h"
#include "core/macros.h"

// Jni++ utils.
#include "utils/StaticString.h"
#include "utils/StaticString.operations.h"

// Jni++ type marshaling.
#include "marshaling/JavaTypeTraits.h"
#include "marshaling/EnvironmentTraits.h"
#include "marshaling/ArrayTranslationTraits.h"
#include "marshaling/NativeTypeTraits.h"

// Jni++ forward declarations and useful types.
#include "utils/forwards.h"
#include "utils/types.h"

// Jni++ wrap for Java classes.
#include "handles/Class.h"
#include "handles/Object.h"
#include "marshaling/NativeTypeTraits.Object.h"
#include "marshaling/NativeTypeTraits.Class.h"

// Jni++ wrap for Java class fields.
#include "handles/MemberField.h"
#include "handles/StaticField.h"

// Jni++ wrap for Java functions.
#include "utils/MemberFunctionInvocation.h"
#include "utils/StaticFunctionInvocation.h"
#include "handles/MemberFunction.h"
#include "handles/StaticFunction.h"

// Some crucial Jni++ types.
#include "utils/NativeFunction.h"
#include "utils/NativeFunction.utils.h"
#include "utils/NativeFunction.macros.h"

// Jni++ major utility - virtual machine wrap.
#include "utils/HandlesCacheEntry.h"
#include "utils/CachedHandles.h"
#include "utils/VirtualMachine.h"
#include "utils/Environment.h"

// Deferred implementation of Jni++ functionality.
#include "utils/CachedHandles.inl"
#include "utils/VirtualMachine.inl"
#include "utils/Environment.inl"
#include "utils/NativeFunction.utils.inl"
#include "handles/Object.inl"
#include "handles/MemberField.inl"
#include "handles/StaticField.inl"
#include "handles/MemberFunction.inl"
#include "handles/StaticFunction.inl"
#include "utils/MemberFunctionInvocation.inl"
#include "utils/StaticFunctionInvocation.inl"
#include "marshaling/NativeTypeTraits.FromJava.inl"
#include "marshaling/NativeTypeTraits.ToJava.inl"
#include "marshaling/ArrayTranslationTraits.FromJava.inl"
#include "marshaling/ArrayTranslationTraits.ToJava.inl"

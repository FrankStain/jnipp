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
};


// Jni++ configuration.
#include <jnipp/core/configuration.h>

// Most major system includes.
#include <cstdint>
#include <string>
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
#include <jnipp/core/logging.h>
#include <jnipp/core/macros.h>

// Jni++ utils.
#include <jnipp/utils/StaticString.h>
#include <jnipp/utils/StaticString.operations.h>

// Jni++ type marshaling.
#include <jnipp/marshaling/JavaTypeTraits.h>
#include <jnipp/marshaling/EnvironmentTraits.h>
#include <jnipp/marshaling/ArrayTranslationTraits.h>
#include <jnipp/marshaling/NativeTypeTraits.h>

// Jni++ forward declarations and useful types.
#include <jnipp/utils/forwards.h>
#include <jnipp/utils/types.h>

// Jni++ wrap for Java classes.
#include <jnipp/handles/Class.h>
#include <jnipp/handles/Object.h>
#include <jnipp/marshaling/NativeTypeTraits.Object.h>
#include <jnipp/marshaling/NativeTypeTraits.Class.h>

// Jni++ wrap for Java class fields.
#include <jnipp/handles/MemberField.h>
#include <jnipp/handles/StaticField.h>

// Jni++ wrap for Java functions.
#include <jnipp/utils/MemberFunctionInvocation.h>
#include <jnipp/utils/StaticFunctionInvocation.h>
#include <jnipp/handles/MemberFunction.h>
#include <jnipp/handles/StaticFunction.h>

// Some crucial Jni++ types.
#include <jnipp/utils/NativeFunction.h>
#include <jnipp/utils/NativeFunction.utils.h>
#include <jnipp/utils/NativeFunction.macros.h>

// Jni++ major utility - virtual machine wrap.
#include <jnipp/utils/VirtualMachine.h>
#include <jnipp/utils/Environment.h>

// Deferred implementation of Jni++ functionality.
#include <jnipp/utils/Environment.inl>
#include <jnipp/utils/NativeFunction.utils.inl>
#include <jnipp/handles/Object.inl>
#include <jnipp/handles/MemberField.inl>
#include <jnipp/handles/StaticField.inl>
#include <jnipp/handles/MemberFunction.inl>
#include <jnipp/handles/StaticFunction.inl>
#include <jnipp/utils/MemberFunctionInvocation.inl>
#include <jnipp/utils/StaticFunctionInvocation.inl>
#include <jnipp/marshaling/NativeTypeTraits.FromJava.inl>
#include <jnipp/marshaling/NativeTypeTraits.ToJava.inl>
#include <jnipp/marshaling/ArrayTranslationTraits.FromJava.inl>
#include <jnipp/marshaling/ArrayTranslationTraits.ToJava.inl>

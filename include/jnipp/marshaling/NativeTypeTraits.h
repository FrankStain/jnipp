// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
namespace Marshaling
{
	/// @brief	Common specification of type translation traits.
	template< typename TNativeType >
	struct NativeTypeTraits;


	/// @brief	JNI signature of arbitrary native type.
	template< typename TNativeType >
	using TypeSignature = typename NativeTypeTraits<TNativeType>::Signature;

	template< typename TNativeType >
	using JavaType = typename NativeTypeTraits<TNativeType>::JavaType;


	/**
		@brief	Regular converting function from Java type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, Java-side.
		@param	destination	Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline void FromJava( const JavaType<TNativeType>& source, TNativeType& destination )
	{
		NativeTypeTraits<TNativeType>::FromJava( source, destination );
	};

	/**
		@brief	Regular converting function from C++ type to Java one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@param	destination	Final storage of converted value, Java-side.
	*/
	template< typename TNativeType >
	inline void ToJava( const TNativeType& source, JavaType<TNativeType>& destination )
	{
		NativeTypeTraits<TNativeType>::ToJava( source, destination );
	};

	/**
		@brief	NRVO-optimizable converting function from Java type to C++ one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, Java-side.
		@return				Final storage of converted value, C++-side.
	*/
	template< typename TNativeType >
	inline TNativeType FromJava( const JavaType<TNativeType>& source )
	{
		TNativeType destination;
		NativeTypeTraits<TNativeType>::FromJava( source, destination );
		return destination;
	};

	/**
		@brief	NRVO-optimizable converting function from C++ type to Java one.
		@tparam	TNativeType	C++ type of value to be converted.
		@param	source		Initial storage of value, C++-side.
		@return				Final storage of converted value, Java-side.
	*/
	template< typename TNativeType >
	inline JavaType<TNativeType> ToJava( const TNativeType& source )
	{
		JavaType<TNativeType> destination;
		NativeTypeTraits<TNativeType>::ToJava( source, destination );
		return destination;
	};


	/// @brief	Traits specification for native `void` type.
	template<>
	struct NativeTypeTraits<void> : EnvironmentTraits<void>, JavaTypeTraits<void>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= void;

		/// @brief	JNI representation of Java type.
		using JavaType		= void;

		/// @brief	Type translation from Java space to C++ space.
		//static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		//static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `bool` type.
	template<>
	struct NativeTypeTraits<bool> : EnvironmentTraits<jboolean>, JavaTypeTraits<jboolean>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= bool;

		/// @brief	JNI representation of Java type.
		using JavaType		= jboolean;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `char16_t` type.
	template<>
	struct NativeTypeTraits<char16_t> : EnvironmentTraits<jchar>, JavaTypeTraits<jchar>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= char16_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jchar;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `int8_t` type.
	template<>
	struct NativeTypeTraits<int8_t> : EnvironmentTraits<jbyte>, JavaTypeTraits<jbyte>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= int8_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jbyte;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `int16_t` type.
	template<>
	struct NativeTypeTraits<int16_t> : EnvironmentTraits<jshort>, JavaTypeTraits<jshort>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= int16_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jshort;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `int32_t` type.
	template<>
	struct NativeTypeTraits<int32_t> : EnvironmentTraits<jint>, JavaTypeTraits<jint>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= int32_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jint;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `int64_t` type.
	template<>
	struct NativeTypeTraits<int64_t> : EnvironmentTraits<jlong>, JavaTypeTraits<jlong>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= int64_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jlong;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `uint8_t` type.
	template<>
	struct NativeTypeTraits<uint8_t> : EnvironmentTraits<jshort>, JavaTypeTraits<jshort>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= uint8_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jshort;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `uint16_t` type.
	template<>
	struct NativeTypeTraits<uint16_t> : EnvironmentTraits<jint>, JavaTypeTraits<jint>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= uint16_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jint;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `uint32_t` type.
	template<>
	struct NativeTypeTraits<uint32_t> : EnvironmentTraits<jlong>, JavaTypeTraits<jlong>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= uint32_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jlong;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `uint64_t` type.
	template<>
	struct NativeTypeTraits<uint64_t> : EnvironmentTraits<jlong>, JavaTypeTraits<jlong>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= uint64_t;

		/// @brief	JNI representation of Java type.
		using JavaType		= jlong;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `float` type.
	template<>
	struct NativeTypeTraits<float> : EnvironmentTraits<jfloat>, JavaTypeTraits<jfloat>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= float;

		/// @brief	JNI representation of Java type.
		using JavaType		= jfloat;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `double` type.
	template<>
	struct NativeTypeTraits<double> : EnvironmentTraits<jdouble>, JavaTypeTraits<jdouble>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 0;

		/// @brief	C++ native type.
		using NativeType	= double;

		/// @brief	JNI representation of Java type.
		using JavaType		= jdouble;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `const char*` type.
	template<>
	struct NativeTypeTraits<const char*> : EnvironmentTraits<jobject>, JavaTypeTraits<jstring>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	C++ native type.
		using NativeType	= const char*;

		/// @brief	JNI representation of Java type.
		using JavaType		= jstring;

		/// @brief	Type translation from Java space to C++ space.
		//static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `const char16_t*` type.
	template<>
	struct NativeTypeTraits<const char16_t*> : EnvironmentTraits<jobject>, JavaTypeTraits<jstring>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	C++ native type.
		using NativeType	= const char16_t*;

		/// @brief	JNI representation of Java type.
		using JavaType		= jstring;

		/// @brief	Type translation from Java space to C++ space.
		//static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `std::string` type.
	template<>
	struct NativeTypeTraits<std::string> : EnvironmentTraits<jobject>, JavaTypeTraits<jstring>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	C++ native type.
		using NativeType	= std::string;

		/// @brief	JNI representation of Java type.
		using JavaType		= jstring;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `std::u16string` type.
	template<>
	struct NativeTypeTraits<std::u16string> : EnvironmentTraits<jobject>, JavaTypeTraits<jstring>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	C++ native type.
		using NativeType	= std::u16string;

		/// @brief	JNI representation of Java type.
		using JavaType		= jstring;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};

	/// @brief	Traits specification for native `std::u16string` type.
	template< typename TNativeElementType, typename TAllocatorType >
	struct NativeTypeTraits< std::vector<TNativeElementType, TAllocatorType> > : EnvironmentTraits<jobject>
	{
		/// @brief	Count of local references required to store this type in Java local frame.
		constexpr static const size_t LOCAL_FRAME_SIZE = 1;

		/// @brief	Java type signature.
		using Signature		= ArrayName<TypeSignature<TNativeElementType>>;

		/// @brief	C++ native type.
		using NativeType	= std::vector<TNativeElementType, TAllocatorType>;

		/// @brief	JNI representation of Java type.
		using JavaType		= jarray;

		/// @brief	Type translation from Java space to C++ space.
		static inline void FromJava( const JavaType& source, NativeType& destination );

		/// @brief	Type translation from C++ space to Java space.
		static inline void ToJava( const NativeType& source, JavaType& destination );
	};
};
};

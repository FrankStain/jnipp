// Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
// Apache 2.0 License
#pragma once


namespace Jni
{
	template< typename... TNativeArguments >
	Object Object::NewObject( const Class& class_handle, const TNativeArguments&... arguments )
	{
		constexpr const size_t LOCAL_FRAME_SIZE = Utils::TotalLocalFrame<TNativeArguments...>::RESULT;
		
		JNI_RETURN_IF_E( !VirtualMachine::IsValid(), {}, "%s:%d - Attempt to use Uninitialized virtual machine.", __func__, __LINE__ );

		const FunctionHandle<void, TNativeArguments...> construction_func{ class_handle, "<init>" };
		JNI_RETURN_IF_E(
			!construction_func,
			{},
			"Failed to locate proper constructor with signature `%s` for object `%s`.", construction_func.GetSignature(), class_handle.GetName().c_str()
		);

		auto local_env = VirtualMachine::GetLocalEnvironment();
		JNI_RETURN_IF_E( LOCAL_FRAME_SIZE && ( local_env->PushLocalFrame( LOCAL_FRAME_SIZE ) != JNI_OK ), {}, "Failed to push JVM local frame with size %d.", LOCAL_FRAME_SIZE );

		Object result_handle;
		result_handle.AcquireObjectRef( local_env->NewObject( *class_handle, *construction_func, Jni::Marshaling::ToJava( arguments )... ) );
		result_handle.m_class_handle = class_handle;

		// In case of exception the empty value will be returned.
		if( local_env->ExceptionCheck() == JNI_TRUE )
		{
			local_env->ExceptionDescribe();
			local_env->ExceptionClear();
			result_handle.Invalidate();
		};

		JNI_RETURN_IF( LOCAL_FRAME_SIZE == 0, result_handle );
		local_env->PopLocalFrame( nullptr );
		return result_handle;
	};
};

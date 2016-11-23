# Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
# Apache 2.0 License


# Looks for a files in requested tree of folders.
define lookup-files
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call lookup-files, $(e)))
endef


# Init the building section for project.
PROJECT_PATH	:= $(call my-dir)
LOCAL_PATH		:= $(PROJECT_PATH)/source
include $(CLEAR_VARS)

LOCAL_MODULE			:= jnipp
LOCAL_EXPORT_C_INCLUDES	:= $(PROJECT_PATH)/include
LOCAL_C_INCLUDES		:= $(LOCAL_EXPORT_C_INCLUDES)
LOCAL_SRC_FILES			:= $(patsubst $(LOCAL_PATH)/%, %, $(filter %.cpp, $(call lookup-files, $(LOCAL_PATH))))
LOCAL_CPP_FEATURES		:= rtti exceptions
LOCAL_EXPORT_LDLIBS		:= -latomic -llog
LOCAL_CPPFLAGS			:= -std=c++11 -Wno-format-security
LOCAL_EXPORT_CPPFLAGS	:= -Wno-format-security

# Build rules for Android native applications.
include $(BUILD_STATIC_LIBRARY)

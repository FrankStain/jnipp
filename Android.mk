# Copyright since 2016 : Evgenii Shatunov (github.com/FrankStain/jnipp)
# Apache 2.0 License


# Define library paths for BitLight platform.
$(call import-add-path, $(BL_ENGINE_HOME)/projects/build.android)
$(call import-add-path, $(BL_ENGINE_HOME)/third-party/projects/build.android)


# Looks for a files in requested tree of folders.
define lookup-files
    $(wildcard $(1)) $(foreach e, $(wildcard $(1)/*), $(call lookup-files, $(e)))
endef


# Init the building section for project.
LOCAL_PATH := $(call my-dir)/source/
include $(CLEAR_VARS)

LOCAL_MODULE			:= jnipp
LOCAL_EXPORT_C_INCLUDES	:= $(call my-dir)/include
LOCAL_C_INCLUDES		:= $(LOCAL_EXPORT_C_INCLUDES)
LOCAL_SRC_FILES			:= $(patsubst $(LOCAL_PATH)/%, %, $(filter %.cpp, $(call lookup-files, $(LOCAL_PATH))))
LOCAL_CPP_FEATURES		:= rtti exceptions
LOCAL_LDFLAGS			:= -latomic -llog
LOCAL_CPPFLAGS			:= -std=c++11

# Build rules for Android native applications.
include $(BUILD_STATIC_LIBRARY)

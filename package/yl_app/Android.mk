LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE_TAGS := optional

LOCAL_SRC_FILES := $(call all-java-files-under, src)

LOCAL_RESOURCE_DIR += $(LOCAL_PATH)/res

LOCAL_CERTIFICATE := platform

LOCAL_PACKAGE_NAME := hellWorld

LOCAL_JNI_SHARED_LIBRARIES := libhelloWorld

include $(BUILD_PACKAGE)

include $(call all-makefiles-under, $(LOCAL_PATH))

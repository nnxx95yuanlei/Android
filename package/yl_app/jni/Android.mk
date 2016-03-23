LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES := libnativehelper \
                          libandroid_runtime \
                          libcutils \
                          libutils \
                          libylService \
                          libbinder \
                          liblog
LOCAL_C_INCLUDES :=$(shell gettop)/frameworks/yl 

LOCAL_MODULE    := libhelloWorld
LOCAL_SRC_FILES := helloWorld.cpp

include $(BUILD_SHARED_LIBRARY)

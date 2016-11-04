LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
            YlService.cpp \
            IYlService.cpp

LOCAL_SHARED_LIBRARIES:= \
            libbinder \
            libutils \
            libcutils

LOCAL_C_INCLUDE += $(LOCAL_PATH)

LOCAL_MODULE:= libylService

include $(BUILD_SHARED_LIBRARY)



include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
            main_ylservice.cpp

LOCAL_LDFLAGS := -Wl,-hash-style=sysv

LOCAL_SHARED_LIBRARIES:= \
            liblog \
            libutils \
            libbinder \
            libylService \
            libcutils

LOCAL_C_INCLUDE += $(LOCAL_PATH)

LOCAL_CFLAGS += -Wall -Wextra

LOCAL_MODULE:= ylService

LOCAL_32_BIT_ONLY := true

include $(BUILD_EXECUTABLE)


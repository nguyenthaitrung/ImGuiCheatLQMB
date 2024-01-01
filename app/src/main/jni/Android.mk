LOCAL_PATH := $(call my-dir)
MAIN_LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE            := libcurl
LOCAL_SRC_FILES         := LQM/Tools/curl/curl-android-$(TARGET_ARCH_ABI)/lib/libcurl.a

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE            := libssl
LOCAL_SRC_FILES         := LQM/Tools/curl/openssl-android-$(TARGET_ARCH_ABI)/lib/libssl.a

include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE            := libcrypto
LOCAL_SRC_FILES         := LQM/Tools/curl/openssl-android-$(TARGET_ARCH_ABI)/lib/libcrypto.a

include $(PREBUILT_STATIC_LIBRARY)


include $(CLEAR_VARS)
LOCAL_MODULE            := libdobby
LOCAL_SRC_FILES         := LQM/Tools/Dobby/libraries/$(TARGET_ARCH_ABI)/libdobby.a
LOCAL_EXPORT_C_INCLUDES := $(LOCAL_PATH)/LQM/Tools/Dobby/

include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libfoxcheats
LOCAL_SRC_FILES := foxcheats/libs/$(TARGET_ARCH_ABI)/libfoxcheats.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)


LOCAL_MODULE           := main

LOCAL_CFLAGS           := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS           += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS         := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS         += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS          += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE         := arm
LOCAL_LDLIBS           := -llog -landroid -lEGL -lGLESv3 -lGLESv2 -lGLESv1_CM -lz

LOCAL_C_INCLUDES       += $(LOCAL_PATH)
LOCAL_C_INCLUDES       := $(LOCAL_PATH)/LQM/Tools/curl/curl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/LQM/Tools/curl/openssl-android-$(TARGET_ARCH_ABI)/include


FILE_LIST              := $(wildcard $(LOCAL_PATH)/Imgui/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/LQM/IL2CppSDKGenerator/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/Substrate/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/KittyMemory/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/And64InlineHook/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/LQM/Tools/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/Snowflake/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/Main.cpp)

LOCAL_SRC_FILES        := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_STATIC_LIBRARIES := libdobby libcurl libssl libcrypto libfoxcheats
LOCAL_CPP_FEATURES     := exceptions

include $(BUILD_SHARED_LIBRARY)



include $(CLEAR_VARS)
LOCAL_MODULE           := onl

LOCAL_CFLAGS           := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w
LOCAL_CFLAGS           += -fno-rtti -fno-exceptions -fpermissive
LOCAL_CPPFLAGS         := -Wno-error=format-security -fvisibility=hidden -ffunction-sections -fdata-sections -w -Werror -s -std=c++17
LOCAL_CPPFLAGS         += -Wno-error=c++11-narrowing -fms-extensions -fno-rtti -fno-exceptions -fpermissive
LOCAL_LDFLAGS          += -Wl,--gc-sections,--strip-all, -llog
LOCAL_ARM_MODE         := arm
LOCAL_LDLIBS           := -llog -landroid -lEGL -lGLESv3 -lGLESv2 -lGLESv1_CM -lz -lOpenSLES

LOCAL_C_INCLUDES       += $(LOCAL_PATH)
LOCAL_C_INCLUDES       := $(LOCAL_PATH)/LQM/Tools/curl/curl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/LQM/Tools/curl/openssl-android-$(TARGET_ARCH_ABI)/include
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/libzip
LOCAL_C_INCLUDES       += $(LOCAL_PATH)/LQM/Dumper


FILE_LIST              := $(wildcard $(LOCAL_PATH)/Imgui/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/LQM/IL2CppSDKGenerator/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/LQM/Dumper/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/Substrate/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/KittyMemory/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/And64InlineHook/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/LQM/Tools/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/Snowflake/*.c*)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/onl.cpp)
FILE_LIST              += $(wildcard $(LOCAL_PATH)/libzip/*.c)

LOCAL_SRC_FILES        := $(FILE_LIST:$(LOCAL_PATH)/%=%)

LOCAL_STATIC_LIBRARIES := libdobby libcurl libssl libcrypto libfoxcheats

LOCAL_CPP_FEATURES     := exceptions

include $(BUILD_SHARED_LIBRARY)

LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := sanangeles
LOCAL_CFLAGS := -std=c++11
LOCAL_LDLIBS := \
	-lGLESv1_CM \
	-ldl \
	-llog \

LOCAL_SRC_FILES := \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/Android.mk \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/app-android.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/Application.mk \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/bullet.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/demo.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/game_logic.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/graphic_engine.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/obstacle.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/physics_engine.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/space_object.cpp \
	/Users/prohor/Code/ndk-asteroids/app/src/main/jni/space_ship.cpp \

LOCAL_C_INCLUDES += /Users/prohor/Code/ndk-asteroids/app/src/main/jni
LOCAL_C_INCLUDES += /Users/prohor/Code/ndk-asteroids/app/src/debug/jni

include $(BUILD_SHARED_LIBRARY)

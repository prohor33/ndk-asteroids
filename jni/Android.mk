LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sanangeles

LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL

LOCAL_SRC_FILES := \
    app-android.cpp \
    bullet.cpp \
    demo.cpp \
    game_logic.cpp \
    graphic_engine.cpp \
    obstacle.cpp \
    physics_engine.cpp \
    space_object.cpp \
    space_ship.cpp \

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog
include $(BUILD_SHARED_LIBRARY)

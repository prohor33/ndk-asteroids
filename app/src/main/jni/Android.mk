LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := sanangeles

LOCAL_CFLAGS := -DANDROID_NDK \
                -DDISABLE_IMPORTGL
BOOST_LIBRARY := jni/boost_1_54_0
LOCAL_C_INCLUDES += $(BOOST_LIBRARY)
LOCAL_SRC_FILES := \
    app-android.cpp \
    bullet.cpp \
    demo.cpp \
    game.cpp \
    graphic.cpp \
    input.cpp \
    intersection.cpp \
    object.cpp \
    obstacle.cpp \
    physics.cpp \
    ship.cpp \
    utils.cpp \

LOCAL_LDLIBS := -lGLESv1_CM -ldl -llog
include $(BUILD_SHARED_LIBRARY)
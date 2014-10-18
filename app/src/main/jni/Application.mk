APP_PLATFORM := android-8
APP_STL := gnustl_static
APP_CPPFLAGS += -frtti
APP_CPPFLAGS += -fexceptions
#  Enable C++11. However, pthread, rtti and exceptions aren’t enabled
APP_CPPFLAGS += -std=c++11
## Prerequisites:

* Android NDK
* Android SDK **OR** Eclipse ADT Bundle
* Android AVD target installed

## Building project

There are two ways of building Android projects.

1. Android Studio
2. Eclipse
3. Command Line


### Running project from Command Line

    $ cd asteroids-ndk
    $ export NDK_ROOT=/path/to/ndk
    $ ./build_native.sh
    $ ant debug install

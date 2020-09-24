# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.
# 设置 cmake 最小支持版本
cmake_minimum_required(VERSION 3.4.1)

# 创建一个库
add_library(
        # 库名称，比如现在会生成 crash-lib.so
        crash-lib

        # 设置是动态库（SHARED）还是静态库（STATIC）
        SHARED

        # 设置源文件的相对路径
        src/main/cpp/crash.cpp
        #src/main/cpp/dynamic.cpp
        #src/main/cpp/dynamic.h
        )

# 搜索并指定预构建库并将路径存储为变量。
# NDK中已经有一部分预构建库（比如 log），并且ndk库已经是被配置为cmake搜索路径的一部分
# 可以不写 直接在 target_link_libraries 写上log
find_library(
        # 设置路径变量的名称
        log-lib

        # 指定要CMake定位的NDK库的名称
        log)


# 指定CMake应链接到目标库的库。你可以链接多个库，例如构建脚本、预构建的第三方库或系统库。
target_link_libraries( # Specifies the target library.
        crash-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})


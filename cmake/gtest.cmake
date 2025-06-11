# 支持外部项目
include(FetchContent)

# 可选参数 DL_GTEST，默认 OFF（即优先查找系统 gtest）
option(DL_GTEST "Download GoogleTest from source" OFF)

if (DL_GTEST)
    message(STATUS "DL_GTEST=ON: downloading GoogleTest via FetchContent...")

    # 拉取 GoogleTest（推荐使用 release 分支）
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG release-1.17.0
    )
    FetchContent_MakeAvailable(googletest)

else ()
    message(STATUS "DL_GTEST=OFF: using system-installed GoogleTest...")

    find_package(GTest REQUIRED)

    # 打印 GTest 组件状态（可选）
    message(STATUS "Found GTest:")
    message(STATUS "  GTest_INCLUDE_DIRS = ${GTEST_INCLUDE_DIRS}")
    message(STATUS "  GTest_LIBRARIES    = ${GTEST_LIBRARIES}")

endif ()

# 自动查找所有子目录下的 .cpp 和 .c 文件
file(GLOB_RECURSE TEST_SOURCES
        "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/*.c"
)

# 遍历每个 .cpp 文件，生成独立可执行程序
foreach (file_path IN LISTS TEST_SOURCES)
    get_filename_component(file_name ${file_path} NAME_WE)

    add_executable(${file_name} ${file_path})
    target_link_libraries(${file_name}
            PRIVATE
            GTest::gtest
            GTest::gtest_main
            pthread
            common_headers
            utils
            message_router
            iface_user
            impl_user
            iface_device
            impl_device
    )
endforeach ()

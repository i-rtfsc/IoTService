add_library(impl_user_mock OBJECT
        src/MockUserManager.cpp
)

target_include_directories(impl_user_mock PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(impl_user_mock
        PUBLIC
        common_headers
        plugin_factory
        iface_user
)

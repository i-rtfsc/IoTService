add_library(impl_user_default OBJECT
        src/DefaultUserManager.cpp
)

target_include_directories(impl_user_default PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(impl_user_default
        PUBLIC
        common_headers
        plugin_factory
        iface_user
)

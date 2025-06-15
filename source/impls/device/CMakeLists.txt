add_subdirectory(default)

add_library(impl_device SHARED
        $<TARGET_OBJECTS:impl_device_default>
)

target_include_directories(impl_device PUBLIC
        default/include
)

target_link_libraries(impl_device
        PUBLIC
        common_headers
        plugin_factory
        iface_device
)

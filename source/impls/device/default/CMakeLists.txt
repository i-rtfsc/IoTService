add_library(impl_device_default
        src/DefaultDeviceManager.cpp
)

target_include_directories(impl_device_default
        PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(impl_device_default
        common_headers
        plugin_factory
        iface_device
)

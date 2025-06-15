option(ENABLE_AUTH_MOCK "Enable mock for authentication" OFF)
if (ENABLE_AUTH_MOCK)
    add_definitions(-DENABLE_AUTH_MOCK)
endif ()

add_subdirectory(default)
add_subdirectory(mock)

add_library(impl_user SHARED
    $<TARGET_OBJECTS:impl_user_default>
    $<TARGET_OBJECTS:impl_user_mock>
)

target_include_directories(impl_user PUBLIC
    default/include
    mock/include
)

target_link_libraries(impl_user
    PUBLIC
    common_headers
    plugin_factory
    iface_user
)

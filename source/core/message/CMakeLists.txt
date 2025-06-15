add_library(message_router STATIC
        src/MessageRouter.cpp
)

target_include_directories(message_router PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

target_link_libraries(message_router PUBLIC
        common_headers
        task_thread
        plugin_factory
        iface_device
        iface_user
)

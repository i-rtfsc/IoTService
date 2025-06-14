cmake_minimum_required(VERSION 3.16)
project(rust_display NONE)

include(ExternalProject)

ExternalProject_Add(
        rust_display_project
        PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rust_build
        SOURCE_DIR ${RUST_CRATE_DIR}
        CONFIGURE_COMMAND ""
        BUILD_COMMAND cargo build --release
        BUILD_IN_SOURCE 1
        INSTALL_COMMAND ""
        LOG_BUILD ON
        BUILD_BYPRODUCTS ${RUST_TARGET_DIR}/release/lib${RUST_LIB_NAME}.a
)

ExternalProject_Get_Property(rust_display_project binary_dir)

add_library(rust_display STATIC IMPORTED GLOBAL)
add_dependencies(rust_display rust_display_project)

set_target_properties(rust_display PROPERTIES
        IMPORTED_LOCATION "${RUST_TARGET_DIR}/release/lib${RUST_LIB_NAME}.a"
)
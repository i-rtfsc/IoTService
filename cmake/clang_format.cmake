# 设置 clang-format 检查脚本路径
set(CLANG_FORMAT_SCRIPT "${CMAKE_SOURCE_DIR}/cmake/check-clang-format.sh")

# 添加一个全局目标，供其他目标依赖
add_custom_target(clang_format_check
        COMMAND ${CMAKE_COMMAND} -E echo "Running clang-format check..."
        COMMAND ${CLANG_FORMAT_SCRIPT}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)
# 避免重复 include 和定义
if (NOT DEFINED CLANG_FORMAT_CHECK_DEFINED)
    set(CLANG_FORMAT_CHECK_DEFINED TRUE)

    set(CLANG_FORMAT_SCRIPT "${CMAKE_SOURCE_DIR}/check-clang-format.sh")

    # 只在第一次 include 时创建 custom target
    if (NOT TARGET clang_format_check)
        add_custom_target(clang_format_check
                COMMAND ${CMAKE_COMMAND} -E echo "Running clang-format check..."
                COMMAND ${CLANG_FORMAT_SCRIPT}
                WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
    endif ()

    # 保存原始 add_executable（只保存一次）
    if (NOT COMMAND original_add_executable)
        function(original_add_executable)
            _add_executable(${ARGV})
        endfunction()
    endif ()

    # 保存原始 add_library
    if (NOT COMMAND original_add_library)
        function(original_add_library)
            _add_library(${ARGV})
        endfunction()
    endif ()

    # Hook add_executable：构建时自动依赖 clang_format_check
    function(add_executable target)
        _add_executable(${ARGV})
        if (TARGET ${target})
            add_dependencies(${target} clang_format_check)
        endif ()
    endfunction()

    # Hook add_library（可选）
    function(add_library target)
        _add_library(${ARGV})
        if (TARGET ${target})
            add_dependencies(${target} clang_format_check)
        endif ()
    endfunction()
endif ()

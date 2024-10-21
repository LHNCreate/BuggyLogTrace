cmake_minimum_required(VERSION 3.29)
project(BuggyLogTrace)

set(CMAKE_CXX_STANDARD 17)

# 查找 spdlog
find_package(spdlog REQUIRED)

# 包含头文件目录
include_directories(BuggyLog)

# 查找源文件和头文件
file(GLOB_RECURSE source BuggyLog/*.cpp)
file(GLOB_RECURSE header BuggyLog/*.hpp)

# 创建共享库
add_library(BuggyLogTrace SHARED ${source} ${header})

# 设置共享库的输出目录
set_target_properties(BuggyLogTrace PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/build/lib"
)

# 链接 spdlog 并确保它是 PUBLIC 依赖
target_link_libraries(BuggyLogTrace PUBLIC spdlog::spdlog)

# 安装共享库
install(TARGETS BuggyLogTrace
        EXPORT BuggyLogTraceTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# 安装头文件到 include 目录
install(DIRECTORY BuggyLog/ DESTINATION include)

# 为 BuggyLogTrace 生成配置文件
include(CMakePackageConfigHelpers)
configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/cmake/BuggyLogTraceConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/BuggyLogTraceConfig.cmake"
        INSTALL_DESTINATION lib/cmake/BuggyLogTrace
)

# 安装配置文件和导出目标文件
install(FILES "${CMAKE_CURRENT_BINARY_DIR}/BuggyLogTraceConfig.cmake"
        DESTINATION lib/cmake/BuggyLogTrace)

install(EXPORT BuggyLogTraceTargets
        FILE BuggyLogTraceTargets.cmake
        NAMESPACE BuggyLogTrace::
        DESTINATION lib/cmake/BuggyLogTrace)

# Test部分的处理
option(BUILD_TESTS "Build the test target" OFF)
if(BUILD_TESTS)
    add_executable(testlog test/test.cpp)
    target_link_libraries(testlog PRIVATE BuggyLogTrace)
endif()
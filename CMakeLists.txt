cmake_minimum_required(VERSION 3.29)
project(BuggyLogTrace)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog REQUIRED)

include_directories(BuggyLog)

file(GLOB_RECURSE source BuggyLog/*.cpp)
file(GLOB_RECURSE header BuggyLog/*.hpp)
add_library(BuggyLogTrace SHARED "${source}" "${header}")

set_target_properties(BuggyLogTrace PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/build/lib"
)

target_link_libraries(BuggyLogTrace PRIVATE spdlog::spdlog)

# 为库创建导出目标
install(TARGETS BuggyLogTrace
        EXPORT BuggyLogTraceTargets
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
        RUNTIME DESTINATION bin
        INCLUDES DESTINATION include
)

# 安装头文件
install(DIRECTORY BuggyLog/ DESTINATION include)

# 安装Config.cmake文件
install(EXPORT BuggyLogTraceTargets
        FILE BuggyLogTraceConfig.cmake
        NAMESPACE BuggyLogTrace::
        DESTINATION lib/cmake/BuggyLogTrace
)

# Test部分的处理
option(BUILD_TESTS "Build the test target" OFF)

if(BUILD_TESTS)
    add_executable(testlog test/test.cpp)
    target_link_libraries(testlog PRIVATE BuggyLogTrace)
    target_link_libraries(testlog PRIVATE spdlog::spdlog)
endif()
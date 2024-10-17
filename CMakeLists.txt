cmake_minimum_required(VERSION 3.29)
project(BuggyLogTrace)

set(CMAKE_CXX_STANDARD 17)

find_package(spdlog)

include_directories(interface)

file(GLOB_RECURSE source interface/*.cpp)
file(GLOB_RECURSE header interface/*.hpp)
add_library(BuggyLogTrace SHARED "${source}" "${header}")

set_target_properties(BuggyLogTrace PROPERTIES LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_LIST_DIR}/build/lib")

target_link_libraries(BuggyLogTrace PRIVATE spdlog::spdlog)

#test
add_executable(testlog test/test.cpp)
target_link_libraries(testlog PRIVATE BuggyLogTrace)
target_link_libraries(testlog PRIVATE spdlog::spdlog)
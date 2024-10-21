# BuggyLogTrace
log&amp;trace for BuggyAutosar


## compile and install

```bash
mkdir build && cd build
cmake ..
sudo cmake --build . --target install
```

## dependency

-spdlog

### macos

```bash
brew install spdlog
```

## usage

```cmake

find_package(BuggyLogTrace REQUIRED)
add_executable(your_target_name main.cpp)
target_link_libraries(your_target_name PRIVATE BuggyLogTrace::BuggyLogTrace)


### details see tests ###

```
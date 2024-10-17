//
// Created by 李浩楠 on 24-10-17.
//


#include <log.hpp>
#undef LOG_TAG
#define LOG_TAG "i am a tag"
int main(int argc, char *argv[]) {
    init_logger();
    LOG_INFO("This is a info message");
    LOG_WARN("This is a warn message");
    LOG_ERROR("This is an error message");
    LOG_DEBUG("This is a debug message");
    return 0;
}

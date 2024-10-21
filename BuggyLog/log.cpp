//
// Created by 李浩楠 on 24-10-17.
//
#include <log.hpp>


void CustomFormatter::format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest) {
    std::string log_level;
    switch (msg.level) {
        case spdlog::level::trace: log_level = "TRACE";
            break;
        case spdlog::level::debug: log_level = "DEBUG";
            break;
        case spdlog::level::info: log_level = "INFO";
            break;
        case spdlog::level::warn: log_level = "WARN";
            break;
        case spdlog::level::err: log_level = "ERROR";
            break;
        case spdlog::level::critical: log_level = "CRITICAL";
            break;
        default: log_level = "UNKNOWN";
            break;
    }
    dest.append(log_level);
}

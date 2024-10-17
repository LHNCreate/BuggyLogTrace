//
// Created by 李浩楠 on 24-10-17.
//

#ifndef LOG_HPP
#define LOG_HPP

#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

// 自定义日志格式化器
class CustomFormatter : public spdlog::custom_flag_formatter {
public:
    void format(const spdlog::details::log_msg &msg, const std::tm &, spdlog::memory_buf_t &dest) override;

    [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override {
        return std::make_unique<CustomFormatter>();
    }
};

// 初始化日志系统
inline void init_logger() {
    auto formatter = std::make_unique<spdlog::pattern_formatter>();
    formatter->add_flag<CustomFormatter>('L').set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] [%L] [%n] %v%$");
    spdlog::set_formatter(std::move(formatter));
    spdlog::set_level(spdlog::level::trace); // 全局日志级别
}

// 定义懒加载的日志记录器创建函数
inline std::shared_ptr<spdlog::logger> get_logger(const std::string &logger_name) {
    auto logger = spdlog::get(logger_name);
    if (!logger) {
        logger = spdlog::stdout_color_mt(logger_name); // 懒加载创建日志记录器
    }
    return logger;
}

// 定义宏用于日志输出
#define LOG_INFO(...) get_logger(LOG_TAG)->info(__VA_ARGS__)
#define LOG_WARN(...) get_logger(LOG_TAG)->warn(__VA_ARGS__)
#define LOG_ERROR(...) get_logger(LOG_TAG)->error(__VA_ARGS__)
#define LOG_DEBUG(...) get_logger(LOG_TAG)->debug(__VA_ARGS__)

#endif //LOG_HPP

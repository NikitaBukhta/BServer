#include "LoggerInitializer.hpp"
#include "config.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <memory>
#include <filesystem>

namespace server::initializer {

void LoggerInitializer::init() {
    std::filesystem::create_directory("logs");
    
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>("logs/logs.txt", true);

    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [thread %t] [%s][%!] [line %#] %v");
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [thread %t] [%s][%!] [line %#] %v");

    console_sink->set_color_mode(spdlog::color_mode::always);

    auto logger = std::make_shared<spdlog::logger>(common::config::LOG_DOMAIN, spdlog::sinks_init_list{ console_sink, file_sink });
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_on(spdlog::level::debug);
    
    SPDLOG_LOGGER_INFO(logger, "Logger initialized");
}

}   // !server::initializer;
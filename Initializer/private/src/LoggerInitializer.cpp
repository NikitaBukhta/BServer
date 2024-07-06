#include "LoggerInitializer.hpp"
#include "config.hpp"

#include "spdlog/spdlog.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

#include <memory>
#include <filesystem>

namespace server::initializer {

void LoggerInitializer::init() {
    const std::string LOG_FILE_PATH = "logs/log";
    std::filesystem::create_directory("logs");
    
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(generate_log_file_name(LOG_FILE_PATH), true);

    console_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [thread %t] [%s][%!] [line %#] %v");
    file_sink->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%l] [thread %t] [%s][%!] [line %#] %v");

    console_sink->set_color_mode(spdlog::color_mode::always);

    auto logger = std::make_shared<spdlog::logger>(common::config::LOG_DOMAIN, spdlog::sinks_init_list{ console_sink, file_sink });
    spdlog::set_default_logger(logger);
    spdlog::set_level(spdlog::level::debug);
    spdlog::flush_on(spdlog::level::debug);
    
    SPDLOG_LOGGER_INFO(logger, "Logger initialized");
}

std::string LoggerInitializer::current_date_time_as_string(void) {
    // Get the current time using std::chrono
    auto now = std::chrono::system_clock::now();
    
    // Convert the current time to a time_t object
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);
    
    // Convert time_t to a struct tm (broken down time)
    std::tm tm_struct = *std::localtime(&now_c);
    
    // Format the date-time as a string
    std::stringstream ss;
    ss << std::put_time(&tm_struct, "%Y.%m.%d_%H.%M.%S");
    
    return ss.str();
}

std::string LoggerInitializer::generate_log_file_name(const std::string& log_file_name) {
    std::stringstream file_name_stream;
    file_name_stream << log_file_name << "_" << current_date_time_as_string() << ".log";

    return std::move(file_name_stream.str());
}

}   // !server::initializer;
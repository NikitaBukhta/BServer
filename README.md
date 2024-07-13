spdlog turn on DEBUG lvl or switch to anyone:
spdlog/include/spdlog/common.h
#if !defined(SPDLOG_ACTIVE_LEVEL)
    #define SPDLOG_ACTIVE_LEVEL SPDLOG_LEVEL_DEBUG  // or any other;
#endif

macroses for logging:
#ifndef DECLARE_TAG_SCOPE
#define DECLARE_TAG_SCOPE(domain) \
    auto __logger__ = spdlog::get(domain);
#endif  // !DECLARE_TAG_SCOPE

#ifndef LOG_DEBUG
#define LOG_DEBUG(...) \
    SPDLOG_LOGGER_DEBUG(__logger__, __VA_ARGS__);
#endif  // !LOG_DEBUG;

#ifndef LOG_INFO
#define LOG_INFO(...) \
    SPDLOG_LOGGER_INFO(__logger__, __VA_ARGS__);
#endif  // !LOG_INFO;

#ifndef LOG_WARNING
#define LOG_WARNING(...) \
    SPDLOG_LOGGER_WARN(__logger__, __VA_ARGS__);
#endif  // !LOG_WARNING;

#ifndef LOG_ERROR
#define LOG_ERROR(...) \
    SPDLOG_LOGGER_ERROR(__logger__, __VA_ARGS__);
#endif  // !LOG_ERROR;

#ifndef LOG_CRITICAL
#define LOG_CRITICAL(...) \
    SPDLOG_LOGGER_CRITICAL(__logger__, __VA_ARGS__);
#endif  // !LOG_CRITICAL;
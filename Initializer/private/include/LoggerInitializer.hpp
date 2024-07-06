#ifndef __SERVER_INITIALIZER_LOGGERINITIALIZER_HPP__
#define __SERVER_INITIALIZER_LOGGERINITIALIZER_HPP__

#include <string>
namespace server::initializer {

class LoggerInitializer {
public:
    static void init();

private:
    static std::string current_date_time_as_string(void);
    static std::string generate_log_file_name(const std::string& log_file_name);
};

}   // !server::initializer;

#endif  // !__SERVER_INITIALIZER_LOGGERINITIALIZER_HPP__;
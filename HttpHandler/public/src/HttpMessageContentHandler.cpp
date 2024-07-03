#include "HttpMessageContentHandler.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

namespace server::http {

std::string HttpMessageContentHandler::handle_message(const std::string& data) {
    spdlog::info("size = {} | data = {}", data.size(), data);
    std::stringstream response;
    response << "Content-Length: " << 0 << "\r\n";
    response << "Connection: close\r\n\r\n";

    return response.str();
};

}   // !server::http;
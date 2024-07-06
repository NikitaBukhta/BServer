#include "HttpMessageContentHandler.hpp"
#include "HttpContent.hpp"

#include "config.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

namespace server::http {

std::shared_ptr<connection::IContent> HttpMessageContentHandler::handle_message(const std::string& data) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("size = {} | data = {}", data.size(), data);
    auto ret = std::make_shared<HttpContent>();

    std::stringstream response;

    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "Connection: close\r\n\r\n"; 

    ret->set_content(response.str());

    return ret;
};

}   // !server::http;
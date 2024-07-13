#include "HttpMessageContentHandler.hpp"
#include "HttpHeader.hpp"
#include "TextContentSender.hpp"
#include "config.hpp"

#include "spdlog/spdlog.h"
#include "picohttpparser.h"

#include <sstream>

namespace server::http {

std::shared_ptr<connection::IContentSender> HttpMessageContentHandler::handle_message(const std::string& data) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("size = {} | data = {}", data.size(), data);
    // auto ret = std::make_shared<HttpContent>();

    HttpHeader header_request;
    header_request.parse_request(data);

    std::stringstream headers;
    headers << header_request.m_headers[0].name << ": " << header_request.m_headers[0].value << std::endl;

    LOG_DEBUG("start reading headers");

    LOG_DEBUG("Method type = {} | path = {} | http version = {} | headers = {}", header_request.m_method, header_request.m_path, header_request.m_minor_version, headers.str());

    // phr_parse_request()

    std::stringstream response;

    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "Connection: close\r\n\r\n"; 

    auto content = std::make_shared<connection::TextContentSender>();
    content->set_content(response.str());

    return content;
};

}   // !server::http;
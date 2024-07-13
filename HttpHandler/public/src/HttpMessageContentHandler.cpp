#include "HttpMessageContentHandler.hpp"
#include "TextContentSender.hpp"
#include "config.hpp"

#include "spdlog/spdlog.h"
#include "picohttpparser.h"

namespace server::http {

std::shared_ptr<connection::IContentSender> HttpMessageContentHandler::handle_message(const std::string& data) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("size = {} | data = {}", data.size(), data);

    m_buffer_ss << data;
    LOG_DEBUG("Buffer content = {}", m_buffer_ss.str());
    HttpHeader header_request;
    auto parse_result = header_request.parse_request(m_buffer_ss.str());

    switch (parse_result) {
        case HttpHeader::ParsingResultEnum::COMPLETED:
            return on_completed(header_request);
            break;
        case HttpHeader::ParsingResultEnum::NOT_COMPLETED:
            return on_not_completed();
            break;
        case HttpHeader::ParsingResultEnum::PARSE_ERROR:
        case HttpHeader::ParsingResultEnum::UNKNOWN:
        default:
            return on_error();
    }
};

std::shared_ptr<connection::IContentSender> HttpMessageContentHandler::on_completed(HttpHeader& header) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    std::stringstream headers;
    for (auto header : header.m_headers) {
        headers << header.first << ": " << header.second << std::endl;
    }
    LOG_INFO("Method type = {} | path = {} | http version = 1.{} | headers = {}", header.m_method, header.m_path, header.m_minor_version, headers.str());

    m_buffer_ss.str("");
    m_buffer_ss.clear();

    std::stringstream response;

    response << "HTTP/1.1 200 OK\r\n";
    response << "Content-Length: " << 0 << "\r\n";
    response << "Connection: close\r\n\r\n"; 

    auto content = std::make_shared<connection::TextContentSender>();
    content->set_content(response.str());

    return content;
}

std::shared_ptr<connection::IContentSender> HttpMessageContentHandler::on_not_completed() {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("called");
    return std::make_shared<connection::TextContentSender>();
}

std::shared_ptr<connection::IContentSender> HttpMessageContentHandler::on_error() {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("called");
    return nullptr;
}

}   // !server::http;
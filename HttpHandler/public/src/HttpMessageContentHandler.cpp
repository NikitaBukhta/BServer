#include "HttpMessageContentHandler.hpp"
#include "TextContentSender.hpp"
#include "config.hpp"

#include "spdlog/spdlog.h"
#include "picohttpparser.h"

namespace server::http {

void tmp_method() {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);

    server::http::HttpHeader header;
    std::string request =
        "GET /index.html HTTP/1.1\r\n"
        "Host: localhost:8080\r\n"
        "Connection: keep-alive\r\n"
        "Cache-Control: max-age=0\r\n"
        "sec-ch-ua: \"Not/A)Brand\";v=\"8\", \"Chromium\";v=\"126\", \"Google Chrome\";v=\"126\"\r\n"
        "sec-ch-ua-mobile: ?0\r\n"
        "sec-ch-ua-platform: \"Linux\"\r\n"
        "Upgrade-Insecure-Requests: 1\r\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/126.0.0.0 Safari/537.36\r\n"
        "Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,*/*;q=0.8,application/signed-exchange;v=b3;q=0.7\r\n"
        "Sec-Fetch-Site: none\r\n"
        "Sec-Fetch-Mode: navigate\r\n"
        "Sec-Fetch-User: ?1\r\n"
        "Sec-Fetch-Dest: document\r\n"
        "Accept-Encoding: gzip, deflate, br, zstd\r\n"
        "Accept-Language: ru,en;q=0.9,en-US;q=0.8,uk;q=0.7,uk-UA;q=0.6\r\n"
        "Cookie: SL_G_WPT_TO=en; SL_GWPT_Show_Hide_tmp=undefined; SL_wptGlobTipTmp=undefined\r\n\r\n";

    auto result = header.parse_request(request);
    
    if (result == server::http::HttpHeader::ParsingResultEnum::COMPLETED) {
        LOG_INFO("Method: {}", header.m_method);
        LOG_INFO("Path: {}",header.m_path);
        LOG_INFO("HTTP Version: 1.{}",header.m_minor_version);

        for (auto header : header.m_headers) {
            LOG_INFO("{} : {}", header.first, header.second);
            // LOG_INFO("{} : {}", header.m_headers[i].name,std::string(header.m_headers[i].value, header.m_headers[i].value_len));
        }
    } else {
        LOG_INFO("Parsing failed with result: {}", static_cast<int>(result));
    }
}

std::shared_ptr<connection::IContentSender> HttpMessageContentHandler::handle_message(const std::string& data) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("size = {} | data = {}", data.size(), data);

    m_buffer_ss << data;
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
    LOG_INFO("Method type = {} | path = {} | http version = {} | headers = {}", header.m_method, header.m_path, header.m_minor_version, headers.str());

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
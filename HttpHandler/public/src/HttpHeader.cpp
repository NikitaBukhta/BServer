#include "HttpHeader.hpp"

namespace server::http {

HttpHeader::ParsingResultEnum HttpHeader::parse_request(const std::string& http_request) {
    ParsingResultEnum ret;

    const char *tmp_method = nullptr;
    std::size_t method_len = 0;
    const char *tmp_path = nullptr;
    std::size_t path_len = 0;
    struct phr_header headers[100];
    std::size_t num_headers = sizeof(headers) / sizeof(headers[0]); // Установим максимальное количество заголовков
    std::int32_t last_len = 0;

    std::int32_t parse_bytes_consumed = phr_parse_request(http_request.c_str(), http_request.size(), &tmp_method,
        &method_len, &tmp_path, &path_len, &m_minor_version, headers, &num_headers, last_len);

    if (parse_bytes_consumed > 0) {
        ret = ParsingResultEnum::COMPLETED;
        m_method.assign(tmp_method, method_len);
        m_path.assign(tmp_path, path_len);
        convert_headers(headers, num_headers);
    } else if (parse_bytes_consumed <= static_cast<std::int32_t>(ParsingResultEnum::ERROR_VALUE_LIMIT)) {
        ret = ParsingResultEnum::UNKNOWN;
    } else {
        ret = static_cast<ParsingResultEnum>(parse_bytes_consumed);
    }

    return ret;
}

std::string HttpHeader::method(void) const {
    return m_method;
}

std::string HttpHeader::path(void) const {
    return m_path;
}

std::int32_t HttpHeader::minor_version(void) const {
    return m_minor_version;
}

const std::map<std::string, std::string>& HttpHeader::headers(void) const noexcept {
    return m_headers;
}

std::string HttpHeader::header_value(const std::string& header_name) const {
    auto header = m_headers.find(header_name);
    return header != std::end(m_headers) ? header->second : "";
}

void HttpHeader::convert_headers(struct phr_header* headers, std::int32_t headers_count) {
    std::string name;
    std::string value;
    for (int32_t i{0}; i < headers_count; ++i) {
        auto header = headers[i];
        name.assign(header.name, header.name_len);
        value.assign(header.value, header.value_len);
        m_headers[name] = value;
    }
}

}   // !server::http;
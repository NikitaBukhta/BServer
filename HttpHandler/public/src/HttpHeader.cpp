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
    m_last_len = 0;

    std::int32_t parse_bytes_consumed = phr_parse_request(http_request.c_str(), http_request.size(), &tmp_method,
        &method_len, &tmp_path, &path_len, &m_minor_version, headers, &num_headers, m_last_len);

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
#include "HttpHeader.hpp"

namespace server::http {

void HttpHeader::parse_request(const std::string& http_request) {
    const char *tmp_method;
    std::size_t method_len;
    const char *tmp_path;
    std::size_t path_len;
    m_num_headers = 5;
    m_last_len = 0;

    phr_parse_request(http_request.c_str(), http_request.empty() ? 0 : http_request.size(), &tmp_method,
        &method_len, &tmp_path, &path_len, &m_minor_version, m_headers, &m_num_headers, m_last_len);

    m_method.assign(tmp_method, method_len);
    m_path.assign(tmp_path, path_len);
}

}   // !server::http;
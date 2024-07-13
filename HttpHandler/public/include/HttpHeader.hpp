#ifndef __SERVER_HTTPHANDLER_HTTPHEADER_HPP__
#define __SERVER_HTTPHANDLER_HTTPHEADER_HPP__

#include <string>
#include "picohttpparser.h"

namespace server::http {

class HttpHeader {
public:
    void parse_request(const std::string& http_request);

public:
    std::string m_method;
    std::string m_path;
    int m_minor_version;
    struct phr_header m_headers[100];
    std::size_t m_num_headers;
    std::size_t m_last_len;
};

}   // !server::http;

#endif  // !__SERVER_HTTPHANDLER_HTTPHEADER_HPP__;
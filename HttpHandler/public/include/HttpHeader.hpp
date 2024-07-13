#ifndef __SERVER_HTTPHANDLER_HTTPHEADER_HPP__
#define __SERVER_HTTPHANDLER_HTTPHEADER_HPP__

#include <string>
#include <cinttypes>
#include <map>
#include "picohttpparser.h"

namespace server::http {

class HttpHeader {
public:
    enum class ParsingResultEnum : std::int8_t {
        UNKNOWN = INT8_MIN,
        ERROR_VALUE_LIMIT = -3,
        NOT_COMPLETED = -2,
        PARSE_ERROR = -1,
        COMPLETED = 0,
    };

public:
    ParsingResultEnum parse_request(const std::string& http_request);

private:
    void convert_headers(struct phr_header* m_headers, std::int32_t headers_count);

public:
    std::string m_method;
    std::string m_path;
    int m_minor_version;
    std::map<std::string, std::string> m_headers;
    std::size_t m_num_headers;
    std::size_t m_last_len;
};

}   // !server::http;

#endif  // !__SERVER_HTTPHANDLER_HTTPHEADER_HPP__;
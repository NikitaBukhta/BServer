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

    std::string method(void) const;
    std::string path(void) const;
    std::int32_t minor_version(void) const;
    const std::map<std::string, std::string>& headers(void) const noexcept;
    std::string header_value(const std::string& header_name) const;

private:
    void convert_headers(struct phr_header* m_headers, std::int32_t headers_count);

private:
    std::string m_method;
    std::string m_path;
    int m_minor_version;
    std::map<std::string, std::string> m_headers;
};

}   // !server::http;

#endif  // !__SERVER_HTTPHANDLER_HTTPHEADER_HPP__;
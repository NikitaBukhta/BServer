#ifndef __SERVER_HTTPHANDLER_HTTPCONTENT_HPP__
#define __SERVER_HTTPHANDLER_HTTPCONTENT_HPP__

#include "IContent.hpp"

using ContentDataType = std::variant<std::string, server::common::File>;

namespace server::http {

class HttpContent : public connection::IContent {
public:
    ContentDataType content(void) const override;
    bool is_empty(void) const override;
    void set_content(const ContentDataType& val);

private:
    ContentDataType m_content;
};

}   // !server:http

#endif  // !__SERVER_HTTPHANDLER_HTTPCONTENT_HPP__;
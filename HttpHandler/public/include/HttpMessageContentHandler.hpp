#ifndef __SERVER_HTTPHANDLER_HTTPMESSAGECONTENTHANDLER__
#define __SERVER_HTTPHANDLER_HTTPMESSAGECONTENTHANDLER__

#include "IMessageContentHandler.hpp"

namespace server::http
{

class HttpMessageContentHandler : public connection::IMessageContentHandler {
public:
    std::shared_ptr<connection::IContent> handle_message(const std::string& data) override;
};

}   // !server::http;


#endif  // !__SERVER_HTTPHANDLER_HTTPMESSAGECONTENTHANDLER__;
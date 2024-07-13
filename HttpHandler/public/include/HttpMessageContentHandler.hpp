#ifndef __SERVER_HTTPHANDLER_HTTPMESSAGECONTENTHANDLER__
#define __SERVER_HTTPHANDLER_HTTPMESSAGECONTENTHANDLER__

#include "IMessageContentHandler.hpp"
#include "HttpHeader.hpp"

#include <sstream>
namespace server::http
{

class HttpMessageContentHandler : public connection::IMessageContentHandler {
public:
    std::shared_ptr<connection::IContentSender> handle_message(const std::string& data) override;

private:
    std::shared_ptr<connection::IContentSender> on_completed(HttpHeader& header);
    std::shared_ptr<connection::IContentSender> on_not_completed();
    std::shared_ptr<connection::IContentSender> on_error();

private:
    std::stringstream m_buffer_ss;
};

}   // !server::http;


#endif  // !__SERVER_HTTPHANDLER_HTTPMESSAGECONTENTHANDLER__;
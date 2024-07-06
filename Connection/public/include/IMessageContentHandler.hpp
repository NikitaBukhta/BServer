#ifndef __SERVER_CONNECTION_IMESSAGECONTENTHANDLER_HPP__
#define __SERVER_CONNECTION_IMESSAGECONTENTHANDLER_HPP__

#include "IContent.hpp"

#include <string>
#include <memory>

namespace server::connection {

class IMessageContentHandler {
public:
    virtual std::shared_ptr<IContent> handle_message(const std::string& data) = 0;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_IMESSAGECONTENTHANDLER_HPP__;
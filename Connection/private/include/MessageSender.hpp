#ifndef __SERVER_CONNECTION_MESSAGESENDER_HPP__
#define __SERVER_CONNECTION_MESSAGESENDER_HPP__

#include "Socket.hpp"

#include <memory>

namespace server::connection {

class MessageSender {
public:
    MessageSender(std::weak_ptr<common::Socket> socket);

    std::int32_t send(const std::string& data);

private:
    std::shared_ptr<common::Socket> m_socket;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_MESSAGESENDER_HPP__;
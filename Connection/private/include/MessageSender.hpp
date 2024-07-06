#ifndef __SERVER_CONNECTION_MESSAGESENDER_HPP__
#define __SERVER_CONNECTION_MESSAGESENDER_HPP__

#include "Socket.hpp"
#include "IContent.hpp"

#include <memory>

namespace server::connection {

class MessageSender {
public:
    MessageSender(std::weak_ptr<common::Socket> socket);

    std::int32_t send(const std::weak_ptr<IContent> content_weak);

private:
    std::int32_t send_text(const std::string& text);
    std::int32_t send_file(const common::File& file);

private:
    std::shared_ptr<common::Socket> m_socket;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_MESSAGESENDER_HPP__;
#include "MessageSender.hpp"

#include <sstream>

namespace server::connection {

MessageSender::MessageSender(std::weak_ptr<common::Socket> socket)
    : m_socket{socket.lock()}
{

}

std::int32_t MessageSender::send(const std::string& data) {
    std::int32_t data_sent = m_socket->send(data);

    return data_sent;
}

}   // !server::connection;
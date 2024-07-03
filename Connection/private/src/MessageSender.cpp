#include "MessageSender.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

namespace server::connection {

MessageSender::MessageSender(std::weak_ptr<common::Socket> socket)
    : m_socket{socket.lock()}
{

}

std::int32_t MessageSender::send(const std::string& data) {
    spdlog::debug("bytes count = {} | data = {}", data.size(), data);

    std::int32_t data_sent = m_socket->send(data);

    spdlog::info("sent {} bytes", data_sent);

    return data_sent;
}

}   // !server::connection;
#include "MessageSender.hpp"

#include "config.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

namespace server::connection {

MessageSender::MessageSender(std::weak_ptr<common::Socket> socket)
    : m_socket{socket.lock()}
{
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("called");
}

std::int32_t MessageSender::send(const std::string& data) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_DEBUG("bytes count = {} | data = {}", data.size(), data);

    std::int32_t data_sent = m_socket->send(data);

    LOG_INFO("sent {} bytes", data_sent);

    return data_sent;
}

}   // !server::connection;
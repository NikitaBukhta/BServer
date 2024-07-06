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

std::int32_t MessageSender::send(const std::weak_ptr<IContent> content_weak) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_DEBUG("called");

    auto content = content_weak.lock();
    auto data = content->content();

    if (auto value = std::get_if<std::string>(&data)) {
        return send_text(*value);
    } else if (auto value = std::get_if<common::File>(&data)) {
        return send_file(*value);
    } else {
        LOG_WARNING("Data type doesn't handled")
    }

    return -1;
}

std::int32_t MessageSender::send_text(const std::string& text) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_DEBUG("bytes count = {} | text = {}", text.size(), text);

    std::int32_t data_sent = m_socket->send(text);

    LOG_INFO("sent {} bytes", data_sent);

    return data_sent;
}

std::int32_t MessageSender::send_file(const common::File& file) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);

    auto sent_bytes = m_socket->sendfile(file);

    if (sent_bytes == file.size()) {
        LOG_DEBUG("Sent file: happened successfull. Was sent {} bytes", sent_bytes);
    } else {
        LOG_ERROR("Error sending file. Bytes sent = {}; total size = {}; error = {}", sent_bytes, file.size(), m_socket->latest_error());
    }

    return sent_bytes;
}

}   // !server::connection;
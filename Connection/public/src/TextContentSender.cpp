#include "TextContentSender.hpp"
#include "config.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

namespace server::connection {

std::string TextContentSender::to_string(void) const {
    std::stringstream ret_ss;
    ret_ss << "content type = txt | content length = " << m_content.size() << " | content = " << m_content;
    return ret_ss.str();
}

bool TextContentSender::is_empty(void) const {
    return m_content.empty();
}

void TextContentSender::send(std::weak_ptr<common::Socket> weak_socket) const {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_DEBUG("called");

    auto socket = weak_socket.lock();

    std::int32_t data_sent = socket->send(m_content);

    LOG_INFO("sent {} / {} bytes", data_sent, m_content.size() * sizeof(char));
}

void TextContentSender::set_content(const std::string& val) {
    m_content = val;
}

void TextContentSender::set_content(std::string&& val) {
    m_content = std::move(val);
}

}   // !server::connection;


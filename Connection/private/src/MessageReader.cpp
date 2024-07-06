#include "MessageReader.hpp"

#include "config.hpp"

#include "spdlog/spdlog.h"

#include <sstream>

namespace server::connection {

MessageReader::MessageReader(std::weak_ptr<common::Socket> socket, std::int32_t read_buf_size)
    : m_socket{socket.lock()}
    , m_read_buf_size{read_buf_size}
{
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("called");
}

std::string MessageReader::read(void) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("Reading socket = {}", m_socket->to_string());

    std::string read_buf;
    std::stringstream ret_buf;

    while (m_socket->read(read_buf, m_read_buf_size) > 0) {
        LOG_DEBUG("read = {} bytes | data = {} ", read_buf.size(), read_buf);
        ret_buf << read_buf;
        read_buf.clear();
    }

    LOG_DEBUG("finished");

    return ret_buf.str();
}

}   // !server::connection;
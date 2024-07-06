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

std::pair<std::string, MessageReader::MessageStatusEnum> MessageReader::read(void) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("Reading socket = {}", m_socket->to_string());

    std::string read_buf;
    MessageReader::MessageStatusEnum read_status = MessageStatusEnum::ERROR;

    auto bytes_read = m_socket->read(read_buf, m_read_buf_size) > 0;
    LOG_DEBUG("read = {} bytes | data = {} ", read_buf.size(), read_buf);

    if (bytes_read == -1) {
        read_status = MessageStatusEnum::ERROR;
    } else if (bytes_read == 0) {
        read_status = MessageStatusEnum::DISCONNECT;
    } else if (bytes_read > 0) {
        read_status = MessageStatusEnum::SUCCESS;
    }

    return {read_buf, read_status};
}

std::string MessageReader::lastest_error(void) {
    return std::move(m_socket->latest_error());
}

}   // !server::connection;
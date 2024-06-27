#include "MessageReader.hpp"

#include <sstream>

namespace server::connection {

MessageReader::MessageReader(std::weak_ptr<common::Socket> socket, std::int32_t read_buf_size)
    : m_socket{socket.lock()}
    , m_read_buf_size{read_buf_size}
{

}

std::string MessageReader::read(void) {
    std::string read_buf;
    std::stringstream ret_buf;

    while (m_socket->read(read_buf, m_read_buf_size) > 0) {
        ret_buf << read_buf;
        read_buf.clear();
    }

    return ret_buf.str();
}

}   // !server::connection;
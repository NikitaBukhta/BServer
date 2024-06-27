#ifndef __SERVER_CONNECTION_MESSAGEREADER_HPP__
#define __SERVER_CONNECTION_MESSAGEREADER_HPP__

#include "Socket.hpp"

#include <memory>

namespace server::connection {

class MessageReader {
public:
    MessageReader(std::weak_ptr<common::Socket> socket, std::int32_t read_buf_size = BUFSIZ);

    std::string read(void);

private:
    std::shared_ptr<common::Socket> m_socket;
    std::int32_t m_read_buf_size;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_MESSAGEREADER_HPP__;
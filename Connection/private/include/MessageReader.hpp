#ifndef __SERVER_CONNECTION_MESSAGEREADER_HPP__
#define __SERVER_CONNECTION_MESSAGEREADER_HPP__

#include "Socket.hpp"

#include <memory>

namespace server::connection {

class MessageReader {
public:
    enum class MessageStatusEnum : int8_t {
        ERROR = -1,
        DISCONNECT = 0,
        SUCCESS = 1,
        COUNT = 3
    };

public:
    MessageReader(std::weak_ptr<common::Socket> socket, std::int32_t read_buf_size = BUFSIZ);

    /* Return values:
     *  std::string - read content;
     *  std::int32_t - bytes read. if read size == -1, the error was occured;
     */
    std::pair<std::string, MessageStatusEnum> read(void);

    std::string lastest_error(void);

private:
    std::shared_ptr<common::Socket> m_socket;
    std::int32_t m_read_buf_size;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_MESSAGEREADER_HPP__;
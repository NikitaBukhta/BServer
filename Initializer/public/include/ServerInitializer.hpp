#ifndef __SERVER_INITIALIZER_SERVERINITIALIZER__
#define __SERVER_INITIALIZER_SERVERINITIALIZER__

#include "ConnectionHandler.hpp"
#include "Socket.hpp"
#include "IRunner.hpp"

#include <vector>
#include <thread>
#include <memory>

namespace server::initializer {

class ServerInitializer : public common::IRunner {
    ServerInitializer(std::uint16_t port, std::uint32_t listen_size, std::weak_ptr<connection::IMessageContentHandler> message_content_handler);

    void run(void) override;

private:
    std::unique_ptr<connection::ConnectionHandler> m_connection_handler;

    std::shared_ptr<common::Socket> m_socket;
    std::uint32_t m_listen_size;

    std::vector<std::thread> m_thread_pull;
};

}   // !server::initializer;

#endif  // !__SERVER_INITIALIZER_SERVERINITIALIZER__;
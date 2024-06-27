#ifndef __SERVER_CONNECTION_CONNECTIONHANDLER_HPP__
#define __SERVER_CONNECTION_CONNECTIONHANDLER_HPP__

#include "IMessageContentHandler.hpp"

#include "Socket.hpp"
#include "IRunner.hpp"

#include <memory>

namespace server::connection {

class ConnectionHandler : public common::IRunner {
public:
    ConnectionHandler(std::weak_ptr<common::Socket> server_socket, std::weak_ptr<IMessageContentHandler> message_content_handler);

    void run(void) override;

private:
    void handle_connect(std::weak_ptr<common::Socket> weak_client_socket);

private:
    std::shared_ptr<common::Socket> m_server_socket;
    std::shared_ptr<IMessageContentHandler> m_message_content_handler;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_CONNECTIONHANDLER_HPP__;
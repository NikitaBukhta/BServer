#include "ConnectionHandler.hpp"
#include "MessageReader.hpp"
#include "MessageSender.hpp"

#include <thread>

namespace server::connection {

ConnectionHandler::ConnectionHandler(std::weak_ptr<common::Socket> server_socket, std::weak_ptr<IMessageContentHandler> message_content_handler)
    : m_server_socket{server_socket.lock()}
    , m_message_content_handler{message_content_handler.lock()}
{

}

void ConnectionHandler::run(void) {
    while (m_server_socket->is_valid()) {
        auto client_socket = std::make_shared<common::Socket>(m_server_socket->accept());

        if (client_socket->is_valid()) {
            std::thread(&ConnectionHandler::handle_connect, this, client_socket).detach();
        }
    }
}

void ConnectionHandler::handle_connect(std::weak_ptr<common::Socket> weak_client_socket) {
    auto client_socket = weak_client_socket.lock();

    MessageReader reader{client_socket};
    MessageSender sender{client_socket};

    auto data = reader.read();
    auto response = m_message_content_handler->handle_message(data);
    sender.send(response);
}

}   // !server::connection;
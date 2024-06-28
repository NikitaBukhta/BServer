#include "ConnectionHandler.hpp"
#include "MessageReader.hpp"
#include "MessageSender.hpp"

#include "spdlog/spdlog.h"

#include <thread>

namespace server::connection {

ConnectionHandler::ConnectionHandler(std::weak_ptr<common::Socket> server_socket, std::weak_ptr<IMessageContentHandler> message_content_handler)
    : m_server_socket{server_socket.lock()}
    , m_message_content_handler{message_content_handler.lock()}
{

}

void ConnectionHandler::run(void) {
    spdlog::info("called");
    while (m_server_socket->is_valid()) {
        spdlog::debug("waiting for connection...");
        auto client_socket = std::make_shared<common::Socket>(m_server_socket->accept());

        if (client_socket->is_valid()) {
            spdlog::debug("Connected socket = ", client_socket->to_string());
            std::thread(&ConnectionHandler::handle_connect, this, client_socket).detach();
        } else {
            spdlog::error("Invalid socket is connected. Socket = ", client_socket->to_string());
            client_socket->close();
        }
    }
}

void ConnectionHandler::handle_connect(std::weak_ptr<common::Socket> weak_client_socket) {
    auto client_socket = weak_client_socket.lock();

    spdlog::info("Socket = ", client_socket->to_string());

    MessageReader reader{client_socket};
    MessageSender sender{client_socket};

    auto data = reader.read();
    spdlog::info("Read bytes = ", data.size(), " | data = ", data);

    auto response = m_message_content_handler->handle_message(data);
    spdlog::info("Sending response bytes = ", response.size(), " | data = ", response);

    sender.send(response);
}

}   // !server::connection;
#include "ConnectionHandler.hpp"
#include "MessageReader.hpp"
#include "MessageSender.hpp"

#include "config.hpp"

#include "spdlog/spdlog.h"

#include <thread>

#include <sstream>

namespace server::connection {

ConnectionHandler::ConnectionHandler(std::weak_ptr<common::Socket> server_socket, std::weak_ptr<IMessageContentHandler> message_content_handler)
    : m_server_socket{server_socket.lock()}
    , m_message_content_handler{message_content_handler.lock()}
{
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("called");
}

void ConnectionHandler::run(void) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);
    LOG_INFO("called");

    while (m_server_socket->is_valid()) {
        LOG_DEBUG("waiting for connection...");
        auto client_socket = std::make_shared<common::Socket>(m_server_socket->accept());

        if (client_socket->is_valid()) {
            LOG_DEBUG("Connected socket = {}", client_socket->to_string());
            std::thread(&ConnectionHandler::handle_connect, this, client_socket).detach();
        } else {
            LOG_ERROR("Invalid socket is connected. Socket = {}", client_socket->to_string());
            client_socket->close();
        }
    }
}

void ConnectionHandler::handle_connect(std::weak_ptr<common::Socket> weak_client_socket) {
    DECLARE_TAG_SCOPE(common::config::LOG_DOMAIN);

    auto client_socket = weak_client_socket.lock();

    LOG_INFO("Socket = {}", client_socket->to_string());

    MessageReader reader{client_socket};
    MessageSender sender{client_socket};
    bool reading_finished{false};

    do {
        auto [data, read_status] = reader.read();
        switch (read_status) {
            case MessageReader::MessageStatusEnum::SUCCESS: {
                auto response = m_message_content_handler->handle_message(data);
                if (response->is_empty()) {
                    continue;
                }
                
                reading_finished = true;
                sender.send(response);
                break;
            }
            case MessageReader::MessageStatusEnum::ERROR:
                LOG_ERROR("Error during read. {}", reader.lastest_error());
                // miss the break to close the connection in the default block;

            default:
                LOG_INFO("Closing the connection");
                // TODO: Implement Disconnector class to disconnect;
                client_socket->close();
                break;
        };
    } while (!reading_finished);
}

}   // !server::connection;
#include "ServerInitializer.hpp"
#include "LoggerInitializer.hpp"

#include "spdlog/spdlog.h"

#include <thread>

namespace server::initializer {

ServerInitializer::ServerInitializer(std::uint16_t port, std::uint32_t listen_size, std::weak_ptr<connection::IMessageContentHandler> message_content_handler) 
    : m_listen_size(listen_size)
{
    LoggerInitializer::init();

    spdlog::info("constructor started");

    m_socket = std::make_shared<common::Socket>();
    m_socket->set_port(port);
    m_connection_handler = std::make_unique<connection::ConnectionHandler>(m_socket, message_content_handler);

    spdlog::debug("constructor finished");
}

void ServerInitializer::run(void) {
    spdlog::info("called");

    if (m_socket->init()) {
        spdlog::critical("Server socket create error. {}", m_socket->latest_error());
        abort();
    }
    if (m_socket->bind()) {
        spdlog::critical("impossible to bind. {}", m_socket->latest_error());
        abort();
    }
    if (m_socket->listen(m_listen_size)) {
        spdlog::critical("impossible to listen. {}", m_socket->latest_error());
        abort();
    }

    m_thread_pull.reserve(1);

    m_thread_pull.push_back(std::thread(&connection::ConnectionHandler::run, m_connection_handler.get()));

    for (auto &item : m_thread_pull) {
        item.join();
    }
}

}   // !server::initializer;
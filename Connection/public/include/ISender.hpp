#ifndef __SERVER_CONNECTION_ISENDER_HPP__
#define __SERVER_CONNECTION_ISENDER_HPP__

#include "Socket.hpp"

#include <memory>

namespace server::connection {

class ISender {
public:
    virtual ~ISender() = default;
    
    virtual void send(std::weak_ptr<common::Socket> weak_socket) const = 0;
};

}   // !server::connection;

#endif  // __SERVER_CONNECTION_ISENDER_HPP__;
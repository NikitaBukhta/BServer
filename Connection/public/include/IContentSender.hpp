#ifndef __SERVER_CONNECTION_ICONTENTSENDER_HPP__
#define __SERVER_CONNECTION_ICONTENTSENDER_HPP__

#include "IContent.hpp"
#include "ISender.hpp"

namespace server::connection {

class IContentSender : public IContent, public ISender {
public:
    virtual ~IContentSender(void) = default;

    virtual std::string to_string(void) const = 0;
    virtual bool is_empty(void) const = 0;

    virtual void send(std::weak_ptr<common::Socket> weak_socket) const = 0;
};

}   // !server::connection;

#endif  // __SERVER_CONNECTION_ICONTENTSENDER_HPP__;
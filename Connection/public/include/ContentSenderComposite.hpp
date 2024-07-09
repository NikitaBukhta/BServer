#ifndef __SERVER_CONNECTION_CONTENTSENDERCOMPOSITE_HPP__
#define __SERVER_CONNECTION_CONTENTSENDERCOMPOSITE_HPP__

#include "IContentSender.hpp"

#include <list>
#include <memory>

namespace server::connection {

class ContentSenderComposite : public IContentSender {
public:
    ~ContentSenderComposite(void) = default;

    std::string to_string(void) const override;
    bool is_empty(void) const override;

    void send(std::weak_ptr<common::Socket> weak_socket) const override;

    void push(std::weak_ptr<IContentSender> elem);

private:
    std::list<std::shared_ptr<IContentSender>> m_content_container;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_CONTENTSENDERCOMPOSITE_HPP__;
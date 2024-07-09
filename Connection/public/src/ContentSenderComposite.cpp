#include "ContentSenderComposite.hpp"

#include <sstream>

namespace server::connection {

std::string ContentSenderComposite::to_string(void) const {
    std::stringstream ss_ret;

    for (const auto& it : m_content_container) {
        ss_ret << it->to_string() << std::endl;
    }

    return ss_ret.str();
}

bool ContentSenderComposite::is_empty(void) const {
    return m_content_container.empty();
}

void ContentSenderComposite::send(std::weak_ptr<common::Socket> weak_socket) const {
    for (const auto& it : m_content_container) {
        it->send(weak_socket);
    }
}

void ContentSenderComposite::push(std::weak_ptr<IContentSender> elem) {
    m_content_container.push_back(elem.lock());
}

}   // !server::connection;

#ifndef __SERVER_CONNECTION_TEXTCONTENTSENDER_HPP__
#define __SERVER_CONNECTION_TEXTCONTENTSENDER_HPP__

#include "IContentSender.hpp"

#include <string>

namespace server::connection {

class TextContentSender : public IContentSender {
public:
    std::string to_string(void) const override;
    bool is_empty(void) const override;

    void send(std::weak_ptr<common::Socket> weak_socket) const override;

    void set_content(const std::string& val);
    void set_content(std::string&& val);

private:
    std::string m_content;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_TEXTCONTENTSENDER_HPP__;
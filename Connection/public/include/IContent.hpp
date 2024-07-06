#ifndef __SERVER_CONNECTION_ICONTENT_HPP__
#define __SERVER_CONNECTION_ICONTENT_HPP__

#include "File.hpp"

#include <variant>
#include <string>

namespace server::connection {

class IContent {
public:
    virtual std::variant<std::string, common::File> content(void) const = 0;
    virtual bool is_empty(void) const = 0;
};

}   // !server::connection;

#endif  // !__SERVER_CONNECTION_ICONTENT_HPP__;
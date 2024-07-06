#include "HttpContent.hpp"

using ContentDataType = std::variant<std::string, server::common::File>;

namespace server::http {

ContentDataType HttpContent::content(void) const {
    return m_content;
}

bool HttpContent::is_empty(void) const {
    if (auto value = std::get_if<std::string>(&m_content)) {
        return value->empty();
    } else if (auto value = std::get_if<common::File>(&m_content)) {
        return value->file_fd() == 0;
    }

    return true;
}

void HttpContent::set_content(const ContentDataType& val) {
    m_content = val;
}

}   // !server::http;
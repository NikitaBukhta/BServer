#ifndef __SERVER_COMMON_IRUNNER_HPP
#define __SERVER_COMMON_IRUNNER_HPP

namespace server::common {

class IRunner {
public:
    virtual void run(void) = 0;
};

}   // !server::common;

#endif  // !__SERVER_COMMON_IRUNNER_HPP;
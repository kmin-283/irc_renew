#ifndef REPLY_HPP
#define REPLY_HPP

#include "Message.hpp"

class Reply
{
private:
    int searchReply(const Message *msg);

public:
    Reply();
    ~Reply();
    int runReply(const Message *msg);
};

#endif
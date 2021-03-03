#ifndef ERRREPLY_HPP
#define ERRREPLY_HPP

#include "Message.hpp"

class ErrReply
{
private:
    int irc_needMoreParam(const Message *msg);
    int irc_alreadyRegistered(const Message *msg);
public:
    ErrReply();
    ~ErrReply();
    int runErrReply(const Message *msg, const int &numericReply);
};


#endif
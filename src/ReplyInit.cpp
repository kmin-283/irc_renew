#include "Reply.hpp"

Reply::Reply()
{
}

Reply::~Reply()
{
}

int  Reply::searchReply(const Message *msg)
{
    switch (djb2_hash(msg->getCommand().c_str()))
    {
    // case djb2_hash():
    //     return irc_(msg);
    case djb2_hash("NICK"):
        return(CONNECT);

    case djb2_hash("USER"):
        return(CONNECT);

    case djb2_hash("OPER"):
        return(CONNECT);

    default:
        return(CONNECT);
    }
}

int Reply::runReply(const Message *msg)
{
    int ret;

    ret = searchReply(msg);
    return (ret);
}
#include "ErrReply.hpp"

ErrReply::ErrReply()
{}

ErrReply::~ErrReply()
{}

int ErrReply::irc_needMoreParam(const Message *msg)
{
    // err = msg->getCommand();
    // err.append(" * :Not enough parameters");
    return (CONN);
}

int ErrReply::irc_alreadyRegistered(const Message *msg)
{
    // IClient *cleint;
    
    // err = this->prefix + " ";

    // err = msg->getCommand();
    
    // user nickname or server name 추가
    
    // err.append(" :Connection already registered");
    return (CONN);
}

int ErrReply::runErrReply(const Message *msg, const int &numericReply)
{
    switch (numericReply)
    {
    case 461:
        return (irc_needMoreParam(msg));
    case 462:
        return (irc_alreadyRegistered(msg));
    default:
        break;
    }
    return (CONN);
}
#include "Command.hpp"

Command::Command()
{
}

Command::~Command()
{}

int Command::mSearchCmd(const Message *msg, const bool &isAlreadyRegistered)
{
    switch (djb2_hash(msg->getCommand().c_str()))
    {
    case djb2_hash("PASS"):
        return irc_pass(msg, isAlreadyRegistered);
    case djb2_hash("NICK"):
        return(CONN);

    case djb2_hash("USER"):
        return(CONN);

    case djb2_hash("OPER"):
        return(CONN);

    // case djb2_hash(something reply):
    //     return (CONN);

    default:
        return(NOT_FOUND);
    }
}

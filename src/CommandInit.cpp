#include "Command.hpp"

Command::Command()
{}

Command::~Command()
{}

int Command::mSearchCmd(Message *sendMsg, const Message *msg, Variables &var, const int &clientId)
{
    switch (djb2_hash(msg->getCommand().c_str()))
    {
    case djb2_hash("PASS"):
        return irc_pass(msg, var, clientId);
    case djb2_hash("NICK"):
        return irc_nick(sendMsg, msg, var, clientId);
    case djb2_hash("USER"):
        return(CONN);
    case djb2_hash("OPER"):
        return(CONN);
    default:
        return(NOT_FOUND);
    }
}

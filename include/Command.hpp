#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Message.hpp"
#include "Variables.hpp"

class Command
{
private:
    
    int irc_pass(const Message *msg, Variables &var, const int &clientId);
    int irc_nick(Message *sendMsg, const Message *msg, Variables &var, const int &clientId);
    int mSetLocalNick(Message *sendMsg, const Message *msg, Variables &var, const int &clientId);
    int mSetRemoteNick(Message *sendMsg, const Message *msg, Variables &var, const int &clientId);

public:
    Command();
    ~Command();
    int mSearchCmd(Message *sendMsg, const Message *msg, Variables &var, const int &clientId);
};


#endif
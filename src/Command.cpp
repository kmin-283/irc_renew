#include "Command.hpp"

int Command::irc_pass(const Message *msg, Variables &var, const int &clientId)
{
    u_short &regis = var.mIsRegistered[clientId];

    if (regis == REGISTERED)
        return (std::stoi(ERR_ALREADYREGISTRED));
    if (msg->getParameters().empty())
        return (std::stoi(ERR_NEEDMOREPARAM));
    if (msg->getParameter(0) == var.global.mPass)
        regis ^= AUTH_PASS;
    return (CONN);
}

int Command::irc_nick(Message *sendMsg, const Message *msg, Variables &var, const int &clientId)
{
    if (msg->getParameters().empty())
        return (std::atoi(ERR_NONICKNAMEGIVEN));
    if (msg->getPrefix().empty() && msg->getParameters().size() == 1)
        return mSetLocalNick(sendMsg, msg, var, clientId);
    return mSetRemoteNick(sendMsg, msg, var, clientId); // nick + hopcount ==> 2
    // remote에서 새로운 nick 등록 -> NICK asd :1
    // remote에서 nick 갱신 -> :<기존> NICK :<신규>
}

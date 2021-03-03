#include "Command.hpp"

int Command::irc_pass(const Message *msg, const bool &isAlreadyRegistered)
{
    std::string err;

    if (isAlreadyRegistered)
        return (std::stoi(ERR_ALREADYREGISTRED));
    if (msg->getParameters().empty())
        return (std::stoi(ERR_NEEDMOREPARAM));
    // if (msg->getParameter(0) == mPass)
    //     mIsRegistered[socket] = true;
    return (CONN);
}
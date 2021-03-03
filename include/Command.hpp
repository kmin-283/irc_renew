#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Message.hpp"

class Command
{
private:
    
    int irc_pass(const Message *msg, const bool &isAlreadyRegistered);

public:
    Command();
    ~Command();
    int mSearchCmd(const Message *msg, const bool &isAlreadyRegistered);
};


#endif
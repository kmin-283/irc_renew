#ifndef COMMAND_HPP
#define COMMAND_HPP

#include "Transmit.hpp"
#include "Message.hpp"

class Command: public Transmit
{
private:
    // std::vector<int (Command::*)(const Message &)> cmds[47];
    
    int searchCmd(const Message &msg);

    int irc_pass(const Message &msg);
public:
    Command();
    ~Command();
    int runCmd(const Message &msg);
};


#endif
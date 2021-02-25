#include "Command.hpp"

constexpr unsigned long djb2_hash_impl(const char* text, unsigned long prev_hash)
{
    return text[0] == '\0' ? prev_hash : djb2_hash_impl( &text[1], prev_hash * 33 ^ static_cast<unsigned long>(text[0]) );
}
 
constexpr unsigned long djb2_hash(const char* text)
{
    return djb2_hash_impl( text, 5381 );
}

Command::Command(/* args */)
{
}

Command::~Command()
{
}

int  Command::searchCmd(const Message &msg)
{
    switch (djb2_hash(msg.getCommand().c_str()))
    {
    case djb2_hash("PASS"):
        return irc_pass(msg);
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

int Command::runCmd(const Message &msg)
{
    int ret;

    ret = searchCmd(msg);
    return (ret);
}
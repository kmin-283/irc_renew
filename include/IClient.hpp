#ifndef ICLIENT_HPP
#define ICLIENT_HPP

#include <string>

class IClient
{
public:
    virtual std::string &getInfo() = 0;
    virtual ~IClient() {}
};
#endif
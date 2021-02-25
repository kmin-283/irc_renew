#ifndef ICLIENT_HPP
#define ICLIENT_HPP

#include <string>

class IClient
{
protected:
    int mSock;
    int sendKbyte;
    int recvKbyte;
public:
    virtual std::string &getInfo(const int &idx) = 0;
    const int getFd() const
    {
        return this->mSock;
    }
    virtual ~IClient() {}
};
#endif
#ifndef REMOTE_SERVER_HPP
#define REMOTE_SERVER_HPP

#include "IClient.hpp"
#include "Channel.hpp"

class RemoteServer: public IClient
{
private:
    std::string mServerName;
public:
    RemoteServer(const int &sock);
    virtual std::string &getInfo(const int &idx);
    virtual ~RemoteServer();
};

#endif
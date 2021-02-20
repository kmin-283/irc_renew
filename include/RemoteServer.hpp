#ifndef REMOTE_SERVER_HPP
#define REMOTE_SERVER_HPP
#include "IClient.hpp"

class RemoteServer: public IClient
{
private:
    /* data */
public:
    RemoteServer(/* args */);
    ~RemoteServer();
};

RemoteServer::RemoteServer(/* args */)
{
}

RemoteServer::~RemoteServer()
{
}

#endif
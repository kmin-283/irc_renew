#include "RemoteServer.hpp"

RemoteServer::RemoteServer(const int &sock)
{
    // tmp
    mSock = sock;
    this->mServerName = "11";
    //
}

RemoteServer::~RemoteServer()
{
    printColorized("goodbye!", GREEN);
}

std::string &RemoteServer::getInfo(const int &idx)
{
    return (this->mServerName);
}
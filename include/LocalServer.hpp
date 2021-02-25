#ifndef LOCALSERVER_HPP
#define LOCALSERVER_HPP

#include "Command.hpp"


class LocalServer
{
private:
    bool run;
    bool mSSLClient;

    const std::string mPass;
    const std::string mPort;
    const std::string mTlsPort;
    const std::string mServerName;
    const std::string mInfo;

    int mNormalSocket;
    int mTlsSocket;
    int mMaxSocket;

    std::set<int> mDirectClient;

    fd_set mReadSockets;

    Command executer;

    void mRenewSocket(const int &socket);
    /*
     * localServerConnection.cpp
     */
    int mAcceptClient(const int &socket);
    int mReceiveMessage(const int &socket);
public:
    LocalServer(const char *password, const char *port);
    ~LocalServer();

    int init(const char *port);
    int connectRemoteServer(const char *RemoteServerInfo);
    int start(void);
};

#endif
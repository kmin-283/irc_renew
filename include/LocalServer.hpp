#ifndef LOCALSERVER_HPP
#define LOCALSERVER_HPP

#include "Executer.hpp"

class LocalServer
{
private:
    bool run;
    bool mSSLClient;

    int mNormalSocket;
    int mTlsSocket;
    int mMaxSocket;

    std::set<int> mDirectClient;


    fd_set mReadSockets;

    Executer executer;

    void mRenewSocket(const int &socket);
    /*
     * localServerConnection.cpp
     */
    int mAcceptClient(const int &socket);
    int mReceiveMessage(const int &socket);
    int mDisconnClient(const int &socket);
public:
    LocalServer();
    ~LocalServer();

    int init();
    int setPassAndPort(const char *password, const char *port);
    int connectRemoteServer(const char *RemoteServerInfo);
    int start(void);
};

#endif
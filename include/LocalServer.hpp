#ifndef LOCALSERVER_HPP
#define LOCALSERVER_HPP

#include "utils.hpp"

class LocalServer
{
private:
    const std::string pass;
    const std::string port;
    const std::string tlsPort;

    int normalSocket;
    int tlsSocket;
    int maxSocket;

    fd_set readSockets;

    void renewSocket(const int &socket);
public:
    LocalServer(const char *password, const char *port);
    ~LocalServer();

    int init(const char *hostname, const char *port);
    int connectRemoteServer(const char *port);
    int start();

};



#endif
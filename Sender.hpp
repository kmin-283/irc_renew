#ifndef TRANSMIT_HPP
#define TRANSMIT_HPP

enum ServerIndex
{
    UPLINKSERVER,
    SERVERNAME,
    HOPCOUNT,
    SERVERINFO,
    TOKEN,
};

enum UserIndex
{
    U_HOSTNAME,
    U_NICK,
    U_ADDRESS,
    U_USERNAME,
    U_REALNAME,
    U_USERMODE,
};

class Sender
{
public:
    Sender(void);
    ~Sender(void);
    // int sendMsg(const Message &msg, const User *user);
    // int sendMsg(const Message &msg, const RemoteServer *rServ);

    // int sendDispatch(const Message &msg, const IClient *client);
    int sendMsg(const Message &msg, const int &clientId);

    void broadcastMsg(const Message &msg, const RemoteServer *rServ);

};

#endif
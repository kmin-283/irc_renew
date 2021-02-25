#ifndef TRANSMIT_HPP
#define TRANSMIT_HPP

#include "RemoteServer.hpp"
#include "User.hpp"
#include "Message.hpp"

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

class Transmit
{
protected:
    /*
     * mDirectServ, User는 해당 명령어에서 새롭게 생성
     */
    std::map<std::string, IClient *> mDirectServ;
    std::map<std::string, IClient *> mDirectUser;
    /*
     * mRemoteServ, User는 해당 명령어에서 새롭게 생성해주어야 함
     */
    std::map<std::string, IClient *> mRemoteServ;
    std::map<std::string, IClient *> mRemoteUser;

public:
    Transmit(void);
    ~Transmit(void);
    int sendMsg(const Message &msg, const User *user);
    int sendMsg(const Message &msg, const RemoteServer *rServ);
    void broadcastMsg(const Message &msg, const RemoteServer *rServ);

};

#endif
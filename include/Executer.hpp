#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include "RemoteServer.hpp"
#include "User.hpp"

// #include "Channel.hpp"

#include "Command.hpp"
#include "Reply.hpp"
#include "ErrReply.hpp"

class Executer
{
private:

    std::vector<bool> mIsRegistered;
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

    // std::map<std::string, Channel> mLocalChannel;
    // std::map<std::string, Channel> mRemoteChannel;
    Command cmd;
    Reply reply;
    ErrReply errReply;

    int mBroadcastMsg(const Message &msg, const RemoteServer *rServ);
    int mSendMsg(const Message &msg, const int &clientId);
public:
    Executer();
    ~Executer();
    int executing(const Message *msg, const int &socket);
};

#endif
#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include "Channel.hpp"
#include "Command.hpp"
#include "Reply.hpp"
#include "ErrReply.hpp"

#include "RemoteServer.hpp"
#include "User.hpp"

#include "Variables.hpp"

class Executer
{
private:

    std::vector<bool> mIsRegistered;
    Variables var;

    // std::string mPass;
    // std::string mPort;
    // std::string mName;
    // std::string mInfo;
    
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
    template <typename _Category>
    int mSetCategory(_Category &category, std::ifstream &f);
    int mSearchCategory(std::ifstream &f, const char *category);
    int mInitFromConf();
    template <typename _Category>
    int mSetKey(_Category &category, char *buf);
public:
    Executer();
    ~Executer();
    int executing(const Message *msg, const int &socket);
    int setPass(const char *passwd);
    int setPort(const char *port);
    const char *getPort() const;
};

#endif
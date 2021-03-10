#ifndef EXECUTER_HPP
#define EXECUTER_HPP

#include "Channel.hpp"
#include "Command.hpp"
#include "Reply.hpp"
#include "ErrReply.hpp"
#include "Variables.hpp"

class Executer
{
private:

    Variables var;

    // Variable로 이동 예정
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
    const std::string &getTlsPort() const;
    const char *getCert() const;
    const char *getKey() const;
};

#endif
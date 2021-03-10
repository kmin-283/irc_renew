#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include "utils.hpp"

#include "RemoteServer.hpp"
#include "User.hpp"

struct vGlobal
{
    std::string mName;
    std::string mInfo;
    std::string mPass;
    std::string mPort;
};

struct vLimits
{
    std::string mMaxNickLength;
};

// struct vChannel
// {

// };


struct vSSL
{
    std::string mCertFile;
    std::string mKeyFile;
    std::string mPort;
};

struct vServer
{
    std::string mName;
    std::string mMyPass;
    std::string mPeerPass;
};

class Variables
{
private:
    void mClearClient();
public:
    vGlobal global;
    vSSL ssl;
    vLimits limits;

    size_t serversIdx;
    std::vector<vServer> servers;

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

    std::map<int, IClient *> mClientFromId;

    std::vector<u_short> mIsRegistered;

    bool mIsBroadcast;


    Variables();
    ~Variables();
    void setKey(vGlobal &global, char *buf);
    void setKey(vServer &server, char *buf);
    void setKey(vSSL &ssl, char *buf);
    void setKey(vLimits &limits, char *buf);

    IClient *findLocalClientByName(const std::string &name);
    IClient *findRemoteClientByName(const std::string &name);
};

#endif
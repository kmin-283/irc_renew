#include "Executer.hpp"

Executer::Executer()
{
    mInitFromConf();
}

Executer::~Executer()
{}


int Executer::executing(const Message *msg, const int &socket)
{
    Message *sendMsg = nullptr;
    int res;
    u_short current = var.mIsRegistered[socket];

    if ((res = cmd.mSearchCmd(sendMsg, msg, var, socket)) >= ERR_REPLY)
        res = errReply.runErrReply(msg, res);
    else if (res == NOT_FOUND)
        res = reply.runReply(msg);
    if (var.mIsBroadcast)
    {
        // mBroadCastMsg(sendMsg);
        std::cout << "broadcast\n";
        var.mIsBroadcast = false;
    }   
    else if (res == CONN)
        // mSendMsg(sendMsg);
    if (sendMsg)
    {
        delete sendMsg;
        sendMsg = nullptr;
    }
    if (DEBUG)
    {
        printColorized("direct user is ", GREEN);
        for (auto it = var.mDirectUser.begin(); it != var.mDirectUser.end(); ++it)
            std::cout << it->first << " ";
        std::cout << std::endl;
        printColorized("remote user is ", GREEN);
        for (auto it = var.mRemoteUser.begin(); it != var.mRemoteUser.end(); ++it)
            std::cout << it->first << " ";
        std::cout << std::endl;
    }
    return (res);
}

int Executer::setPass(const char *passwd)
{
    var.global.mPass = std::string(passwd);
    return (SUCCESS);
}

int Executer::setPort(const char *port)
{
    var.global.mPort = std::string(port);
    return (SUCCESS);
}

const char *Executer::getPort() const
{
    return (var.global.mPort.c_str());
}

const std::string &Executer::getTlsPort() const
{
    return (var.ssl.mPort);
}

const char *Executer::getCert() const
{
    return (var.ssl.mCertFile.c_str());
}

const char *Executer::getKey() const
{
    return (var.ssl.mKeyFile.c_str());
}
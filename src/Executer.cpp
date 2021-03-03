#include "Executer.hpp"

Executer::Executer()
{
    mIsRegistered.assign(10, false);
}

Executer::~Executer()
{}

int Executer::executing(const Message *msg, const int &socket)
{
    int res;
    bool isBroadCast = false;
    bool isAlreadyRegister = false;

    if (mIsRegistered[socket])
        isAlreadyRegister = true;
    if ((res = cmd.mSearchCmd(msg, isAlreadyRegister)) >= ERR_REPLY)
        res = errReply.runErrReply(msg, res);
    else if (res == NOT_FOUND)
        res = reply.runReply(msg);
    // if (isBroadCast)
    //     mBroadCastMsg();
    // else
    //     mSendMsg();
    return (res);
}
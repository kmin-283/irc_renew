#include "Variables.hpp"

Variables::Variables()
    :serversIdx(0), mIsBroadcast(false)
{
    servers.assign(10, vServer());
    mIsRegistered.assign(10, 0);
}

Variables::~Variables()
{
    mClearClient();
}

void Variables::mClearClient()
{
    for(auto it = mDirectUser.begin(); it != mDirectUser.end(); ++it)
        delete it->second;

    for(auto it = mDirectServ.begin(); it != mDirectServ.end(); ++it)
        delete it->second;

    for(auto it = mRemoteUser.begin(); it != mRemoteUser.end(); ++it)
        delete it->second;

    for(auto it = mRemoteServ.begin(); it != mRemoteServ.end(); ++it)
        delete it->second;
}

static void setValue(std::string &val, char *tmp)
{
    char before[256];
    
    while (tmp)
    {
        strcpy(before, tmp + 1);
        if ((tmp = strtok(nullptr, "=")) == nullptr)
           val = std::string(before);
    }
}

void Variables::setKey(vServer &category, char *buf)
{
    char cp[256];

    strcpy(cp, buf);
    char *tmp = strtok(cp, " \t");

    if (!tmp || tmp[0] == ';')
        return;
    switch (djb2_hash(tmp))
    {
    case djb2_hash("Name"):
        return setValue(category.mName, tmp);
    case djb2_hash("MyPassword"):
        return setValue(category.mMyPass, tmp);
    case djb2_hash("PeerPassword"):
        return setValue(category.mPeerPass, tmp);
    default:
        return;
    }
    return;
}

void Variables::setKey(vGlobal &category, char *buf)
{
    char cp[256];

    strcpy(cp, buf);
    char *tmp = strtok(cp, " \t");

    if (!tmp || tmp[0] == ';')
        return;
    switch (djb2_hash(tmp))
    {
    case djb2_hash("Name"):
        return setValue(category.mName, tmp);
    case djb2_hash("Info"):
        return setValue(category.mInfo, tmp);
    case djb2_hash("Password"):
        return setValue(category.mPass, tmp);
    case djb2_hash("Ports"):
        return setValue(category.mPort, tmp);
    default:
        return;
    }
    return;
}

void Variables::setKey(vSSL &category, char *buf)
{
    char cp[256];

    strcpy(cp, buf);
    char *tmp = strtok(cp, " \t");

    if (!tmp || tmp[0] == ';')
        return;
    switch (djb2_hash(tmp))
    {
    case djb2_hash("CertFile"):
        return setValue(category.mCertFile, tmp);
    case djb2_hash("KeyFile"):
        return setValue(category.mKeyFile, tmp);
    case djb2_hash("Ports"):
        return setValue(category.mPort, tmp);
    default:
        return;
    }
    return;
}

void Variables::setKey(vLimits &category, char *buf)
{
    char cp[256];

    strcpy(cp, buf);
    char *tmp = strtok(cp, " \t");

    if (!tmp || tmp[0] == ';')
        return;
    switch (djb2_hash(tmp))
    {
    case djb2_hash("MaxNickLength"):
        return setValue(category.mMaxNickLength, tmp);
    default:
        return;
    }
    return;
}

IClient *Variables::findLocalClientByName(const std::string &name)
{
    std::map<std::string, IClient *>::iterator it;

    if ((it = mDirectUser.find(name)) != mDirectUser.end())
        return it->second;
    if ((it = mDirectServ.find(name)) != mDirectServ.end())
        return it->second;
    return nullptr;
}

IClient *Variables::findRemoteClientByName(const std::string &name)
{
    std::map<std::string, IClient *>::iterator it;

    if ((it = mRemoteUser.find(name)) != mRemoteUser.end())
        return it->second;
    if ((it = mRemoteServ.find(name)) != mRemoteServ.end())
        return it->second;
    return nullptr;
}
#include "Variables.hpp"

Variables::Variables()
    :serversIdx(0)
{
    servers.assign(10, vServer());
}

Variables::~Variables()
{}

static int setValue(std::string &val, char *tmp)
{
    char before[256];
    
    while (tmp)
    {
        strcpy(before, tmp + 1);
        if ((tmp = strtok(nullptr, "=")) == nullptr)
           val = std::string(before);
    }
    return (SUCCESS);
}

int Variables::setKey(vServer &category, char *buf)
{
    char cp[256];

    strcpy(cp, buf);
    char *tmp = strtok(cp, " \t");

    if (tmp[0] == ';')
        return (SUCCESS);
    switch (djb2_hash(tmp))
    {
    case djb2_hash("Name"):
        return setValue(category.mName, tmp);
    case djb2_hash("MyPassword"):
        return setValue(category.mMyPass, tmp);
    case djb2_hash("PeerPassword"):
        return setValue(category.mPeerPass, tmp);
    default:
        return (SUCCESS);
    }
    return (SUCCESS);
}

int Variables::setKey(vGlobal &category, char *buf)
{
    char cp[256];

    strcpy(cp, buf);
    char *tmp = strtok(cp, " \t");

    if (tmp[0] == ';')
        return (SUCCESS);
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
        return (SUCCESS);
    }
    return (SUCCESS);
}
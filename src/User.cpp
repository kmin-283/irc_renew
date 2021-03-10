#include "User.hpp"

User::User(const int &clientId)
{
    mClientId = clientId;
    mInfos.assign(6, "");
}

User::User(const IClient *otherClient)
{
    mInfos.assign(6, "");
    mClientId = otherClient->getClientId();
    // mInfos[UI_HOSTNAME] = otherClient->getInfo(UI_HOSTNAME);
    mInfos[UI_NICK] = otherClient->getInfo(UI_NICK);
    // mInfos[UI_ADDRESS] = otherClient->getInfo(UI_ADDRESS);
    // mInfos[UI_USERNAME] = otherClient->getInfo(UI_USERNAME);
    // mInfos[UI_REALNAME] = otherClient->getInfo(UI_REALNAME);
    // mInfos[UI_USERMODE] = otherClient->getInfo(UI_USERMODE);
}

User::~User()
{}

const std::string &User::getInfo(const int &idx) const
{
    return mInfos[idx];
}
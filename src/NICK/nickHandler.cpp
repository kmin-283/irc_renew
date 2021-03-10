#include "Command.hpp"

static bool isValidNick(const std::string &name)
{
    std::string letSpe(LETTER);
    letSpe.append(SPECIAL);
    
    std::string letSpeDig = letSpe;
    letSpeDig.append(DIGIT);

	for (size_t i = 0; i < name.length(); ++i)
	{
		if (i == 0 && !isCoincide(letSpe, name[i]))
			return false;
		else if (!isCoincide(letSpeDig, name[i]))
			return false;
	}
	return true;
}

int Command::mSetLocalNick(Message *sendMsg, const Message *msg, Variables &var, const int &clientId)
{
    if (msg->getParameters().size() > 1)
        return (std::atoi(ERR_NEEDMOREPARAM));
    
    const std::string &nick = msg->getParameter(0);
    u_short &regis = var.mIsRegistered[clientId];

    if (!isValidNick(nick) || nick.length() > std::stoi(var.limits.mMaxNickLength))
        return (std::atoi(ERR_ERRONEUSNICKNAME));
    if (!(regis & AUTH_PASS))
        return (std::atoi(ERR_NOTAUTHORIZED));

    IClient *user = var.findLocalClientByName(nick);
    
    if (user == nullptr)
        user = var.findRemoteClientByName(nick);
    if (user != nullptr)
        return (std::atoi(ERR_NICKNAMEINUSE));
    if (regis & AUTH_NICK) // 이미 nick이 등록 된 유저.
    {
        IClient *targetToDel = var.mClientFromId[clientId];
        IClient *newUser = new User(targetToDel);
        std::string prefix = targetToDel->getInfo(UI_NICK);
        std::string params(":");
        params.append(nick);

        newUser->setValue(UI_NICK, nick);
        var.mDirectUser.erase(targetToDel->getInfo(UI_NICK));
        delete targetToDel;
        targetToDel = nullptr;
        var.mDirectUser.insert(std::pair<std::string, IClient *>(nick, newUser));
        var.mClientFromId[clientId] = newUser;
        sendMsg = new Message(prefix,"NICK", params);
    }
    else // 새롭게 nick을 등록하는 유저.
    {
        IClient *newUser = new User(clientId);
        std::string params(nick);
        params.append(" :1");

        newUser->setValue(UI_NICK, nick);
        var.mDirectUser.insert(std::pair<std::string, IClient *>(nick, newUser));
        var.mClientFromId.insert(std::pair<int, IClient *>(clientId, newUser));
        regis ^= AUTH_NICK;
        sendMsg = new Message("", "NICK", params);
    }
    var.mIsBroadcast = true;
    return (CONN);
}

int Command::mSetRemoteNick(Message *sendMsg, const Message *msg, Variables &var, const int &clientId)
{
    if (msg->getParameters().size() > 2)
        return (std::atoi(ERR_NEEDMOREPARAM));
    bool isRenewNick = false;
    std::string nick = msg->getParameter(0);
    std::string prefix;
    IClient *remotePrefix = nullptr;
    // prefix가 있는 경우 remoteUser에 존재하는지 확인.
    if (!msg->getPrefix().empty())
    {
        nick = nick.substr(1);
        prefix = msg->getPrefix().substr(1);
        remotePrefix = var.findRemoteClientByName(prefix);
        if (remotePrefix == nullptr)
            return (IGNORE);
        isRenewNick = true;
    }
    if (!isValidNick(nick) || nick.length() > std::stoi(var.limits.mMaxNickLength))
        return (std::atoi(ERR_ERRONEUSNICKNAME));

    IClient *user = var.findLocalClientByName(nick);

    if (user == nullptr)
        user = var.findRemoteClientByName(nick);
    if (user != nullptr)
        return (std::atoi(ERR_NICKNAMEINUSE));
    if (isRenewNick)
    {
        IClient *targetToDel = remotePrefix;
        IClient *newUser = new User(targetToDel);

        newUser->setValue(UI_NICK, nick);
        var.mRemoteUser.erase(targetToDel->getInfo(UI_NICK));
        delete targetToDel;
        targetToDel = nullptr;
        var.mRemoteUser.insert(std::pair<std::string, IClient *>(nick, newUser));
        sendMsg = new Message(*msg);
    }
    else
    {
        IClient *newUser = new User(clientId);
        std::string params(nick);
        int hopCount = std::stoi(msg->getParameter(1).substr(1));
        ++hopCount;
        params.append(" :");
        params.append(std::to_string(hopCount));

        newUser->setValue(UI_NICK, nick);
        var.mRemoteUser.insert(std::pair<std::string, IClient *>(nick, newUser));
        sendMsg = new Message("", "NICK", params);
    }
    var.mIsBroadcast = true;
    return (CONN);
}
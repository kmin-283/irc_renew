#include "LocalServer.hpp"

static struct addrinfo *getAddress(const std::string &info)
{
    int				i;
	int				j;
	std::string		remotePort;
    std::string     remoteAddress;
	struct addrinfo	hints;
	struct addrinfo	*addrInfo;
    
	// TODO address가 제대로 들어왔는지 체크하는 함수필요 할 수 있음
	i = info.rfind(":");
	j = info.rfind(":", i - 1);
	remotePort = info.substr(j + 1, i - j - 1);
	remoteAddress = info.substr(0, j);
    if (!isValidIp(remoteAddress))
       printError("Ip addreess is invalid in function: getAddress() | file: localServerConn.cpp", RED);
    if (!isValidPort(remotePort))
       printError("Port is invalid in function: getAddress() | file: localServerConn.cpp", RED);
	memset(&hints, 0x00, sizeof(struct addrinfo));
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	if (getaddrinfo(remoteAddress.c_str(), remotePort.c_str(), &hints, &addrInfo) != SUCCESS)
		printError("getaddrinfo() error in function: getAddress() | file: localServerConn.cpp", RED);
	return (addrInfo);
}

int LocalServer::connectRemoteServer(const char *remoteServerInfo)
{
    int newSocket;
    int ipVersion;
    struct addrinfo *addrInfo;
    struct addrinfo *addrInfoIter;
    std::string remoteServInfo;

    ipVersion = AF_INET;
    remoteServInfo = std::string(remoteServerInfo);
    addrInfo = getAddress(remoteServInfo);
    if (addrInfo == nullptr)
    {
        freeaddrinfo(addrInfo);
        return (FAIL);
    }
    for (addrInfoIter = addrInfo; addrInfoIter != NULL; addrInfoIter = addrInfoIter->ai_next)
    {
        if (addrInfoIter->ai_family == AF_INET6)
            ipVersion = AF_INET6;
    }
    for (addrInfoIter = addrInfo; addrInfoIter != NULL; addrInfoIter = addrInfoIter->ai_next)
    {
        if (addrInfoIter->ai_family == ipVersion)
        {
            if ((newSocket = socket(addrInfoIter->ai_family, addrInfoIter->ai_socktype, addrInfoIter->ai_protocol)) == FAIL)
                printError("Can't open socket in function: connectRemoteServer() | file: localServerConn.cpp", RED);
            if (connect(newSocket, addrInfoIter->ai_addr, addrInfoIter->ai_addrlen) == FAIL)
            {
                close(newSocket);
                freeaddrinfo(addrInfo);
                return printError("Can't connect socket in function: connectRemoteServer() | file: localServerConn.cpp", RED);
            }
        }
    }
    freeaddrinfo(addrInfo);
    fcntl(newSocket, F_SETFL, O_NONBLOCK);
    this->mRenewSocket(newSocket);

    mDirectClient.insert(newSocket);

    /* sendLocalInfo();*/
    
    /* executer안에서 함수를 생성하여 만들어주어야 함.*/

    // std::string remotePass = remoteServInfo.substr(remoteServInfo.rfind(":") + 1);
    // Message mPassMessage("", "PASS", remotePass);
    // Message serverMessage("", "SERVER", executer.var.global.mName + " 1 " + executer.var.global.mInfo);

    // sender.sendMsg(mPassMessage, static_cast<RemoteServer*>(remoteServer));
    
    // sendMessage에서 해당 클라이언트와 주고받은 메시지를 늘리는 것이 아닌,
    // 해당 클라이언트가 직접 byte를 늘릴 수 있도록 하자
    
    // mDirectClient[newSocket].setCurrentCommand("PASS");
    // this->sendMessage(mPassMessage, &mDirectClient[newSocket]);
    // mDirectClient[newSocket].setCurrentCommand("SERVER");
    // this->sendMessage(serverMessage, &mDirectClient[newSocket]);
    // rOtherServerHandler(Message(), &newClient);

    // printColorize("Remote server connected!", GREEN);
    return (SUCCESS);
}

int LocalServer::mAcceptClient(const int &socket)
{
	int					newSock;
	struct sockaddr_in6	remoteAddress;
	socklen_t			addressLen;

	addressLen = sizeof(struct sockaddr_in);
	if ((newSock = accept(socket, (struct sockaddr*)&remoteAddress, &addressLen)) == FAIL)
		return (printError("Can't accept client in function mAcceptClient | file: LocalServerConn.cpp", RED));
	fcntl(newSock, F_SETFL, O_NONBLOCK);
	mRenewSocket(newSock);
    mDirectClient.insert(newSock);
    if (socket == mTlsSocket)
	{
		mSsl = SSL_new(ctx);
		SSL_set_fd(mSsl, newSock);
		if (SSL_accept(mSsl) == -1)     /* do SSL-protocol accept */
			ERR_print_errors_fp(stderr);
        mSSLSocket.insert(newSock);
	}
	return (printColorized("Someone has connected!", GREEN));
}

static int transCharToMsg(std::string target, std::vector<int> &dst, const char *msg)
{
    /*
     * idx[0]은 prefix와 command사이의 ' '
     * idx[1]은 command와 parameter사이의 ' '
     */
    bool hasPrefix = false;
    size_t idx;

    idx = target.find(' ');
    dst[0] = idx;
    if (target[0] == ':')
        hasPrefix = true;
    if (idx == std::string::npos) // command only
        return (SUCCESS);
    target = target.substr(idx+1);
    idx = target.find(' ');
    // prefix o and param x || prefix x and param o
    if (!hasPrefix) // command + parameter
    {
        dst[1] = dst[0];
        dst[0] = 0;
        return (SUCCESS);
    }
    dst[1] = dst[0] + idx;
    return (SUCCESS);
}

int LocalServer::mReceiveMessage(const int &socket)
{
    std::vector<int> idx(2, 0);
    char		buffer[513];
    char        *tmp;
	int			readResult = 0;
    int         res;
	int			connectionStatus = CONNECT;

    memset(buffer, 0x00, sizeof(buffer));
    if (mSSLClient)
        readResult = SSL_read(mSsl, buffer, sizeof(buffer));
    else
        readResult = recv(socket, buffer, sizeof(buffer), 0);
    std::cout << "Received message : " << buffer << std::endl;
    if (readResult == 0)
        return (mDisconnClient(socket));
    // if (readResult < 0)
    //     return printError("Can't receive message in function mReceiveMessage | file : localServerConn.cpp", RED);
    tmp = strtok(buffer, CR_LF);
    while (tmp)
    {
        std::string info(tmp);
        info = info.substr(0, info.length());
        transCharToMsg(info, idx, tmp);
        Message *recvMsg;

        if (idx[0] == std::string::npos)
            recvMsg = new Message("", info, "");
        else if (idx[0] == 0)
            recvMsg = new Message("", info.substr(0, idx[1]), info.substr(idx[1] + 1));
        else
            recvMsg = new Message(info.substr(0, idx[0]), info.substr(idx[0] + 1, idx[1] - idx[0]), info.substr(idx[1] + 2));
        if (DEBUG)
        {
            if (!recvMsg->getPrefix().empty())
                std::cout << "prefix " << recvMsg->getPrefix() << std::endl;
            if (!recvMsg->getCommand().empty())
                std::cout << "command " << recvMsg->getCommand() << std::endl;
            if (recvMsg->getParameters().size() > 0)
                std::cout << "param " << recvMsg->getParameter(0) << std::endl;
        }
        res = executer.executing(recvMsg, socket);
        delete recvMsg;
        recvMsg = nullptr;
        tmp = strtok(nullptr, CR_LF);
    }
    if (res == DISCONN)
        return (mDisconnClient(socket));
    // if (ret == ERASE_SERVER)
    //     return (mClearServer());
    return (CONN);
}

int LocalServer::mDisconnClient(const int &socket)
{
    // executer.eraseClient(socket); // mIsRegistered에 있는 데이터, mDirect에 있는 데이터 삭제.
    if (mSSLClient)
        mSSLSocket.erase(socket);
    mDirectClient.erase(socket);
    return (SUCCESS);
}
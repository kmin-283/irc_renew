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
    
    std::string remotePass = remoteServInfo.substr(remoteServInfo.rfind(":") + 1);
    Message mPassMessage("", "PASS", remotePass);
    Message serverMessage("", "SERVER", mServerName + " 1 " + mInfo);

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
	// if (socket == this->mTlsSocket)
	// {
	// 	this->ssl = SSL_new(this->ctx);
	// 	SSL_set_fd(this->ssl, newSock);
	// 	if (SSL_accept(this->ssl) == -1)     /* do SSL-protocol accept */
	// 		ERR_print_errors_fp(stderr);
	// 	this->sslFd = newSock;
	// }
	return (printColorized("Someone has connected!", GREEN));
}

static int transCharToMsg(std::vector<int> &dst, const char *msg)
{
    std::string target(msg);
    size_t idx;

    idx = target.find(' ');
    dst[0] = idx;
    if (idx == std::string::npos)
        return (FAIL);
    target = target.substr(idx+1);
    idx = target.find(' ');
    if (idx == std::string::npos) // prefix가 없는 경우
    {
        dst[1] = dst[0];
        dst[0] = -1;
        return (SUCCESS);
    }
    dst[1] = idx;
    return (SUCCESS);
}

int LocalServer::mReceiveMessage(const int &socket)
{
    std::vector<int> idx(2, 0);
    char		buffer[513]; // 한 글자씩 읽는 것 보다 한번에 읽는게 더 빠름.
	int			readResult = 0;
	int			connectionStatus = CONNECT;

    // if (mSSLClient)
        // readResult = SSL_read();
    // else
    memset(buffer, 0x00, sizeof(buffer));
    readResult = recv(socket, buffer, sizeof(buffer), 0);
    if (readResult < 0)
        return printError("Can't receive message in function mReceiveMessage | file : localServerConn.cpp", RED);
    // if (readResult == 0)
    //     return (disconnClient());
    transCharToMsg(idx, buffer);
    std::string info(buffer);
    std::string tmpPrefix;

    if (idx[1] == 0)
        return (CONNECT);
    if (idx[0] == -1)
    {
        tmpPrefix = "";
        idx[0] = 0;
    }
    else
        tmpPrefix = info.substr(0, idx[0]);
    
    Message recvMsg(tmpPrefix, info.substr(idx[0], idx[1] - idx[0]), info.substr(idx[1]+1));

    executer.runCmd(recvMsg);
	// while (42) {
	// 	if (buffer == '\n') {
	// 		// if (mSSLClient)
	// 		// 	std::cout << "SSL ";
	// 		Message recvMsg(info[0], info[1], info[2]); // 0 - prefix, 1 - command, 2 - params
	// 		std::cout << "Reveive message = " << sendMessage.getTotalMessage();
	// 		if (this->commands.find(sendMessage.getCommand()) != this->commands.end()) {
	// 			sender.incrementQueryData(SENDMSG, 1);
	// 			sender.incrementQueryData(SENDBYTES, sendMessage.getTotalMessage().length());
	// 			connectionStatus = (this->*(this->commands[sendMessage.getCommand()]))(sendMessage, &sender);
	// 		}
	// 		sender.clearReceivedMessageStr();
	// 	}
	// 	if (connectionStatus == DISCONNECT || connectionStatus == TOTALDISCONNECT)
	// 		break;
	// }
	// if (readResult == 0)
	// 	this->disconnectClient(sendMessage, &sender);
	// if (connectionStatus == TOTALDISCONNECT)
	// 	this->clearClient();
    return (CONNECT);
}
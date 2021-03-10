#include "LocalServer.hpp"

LocalServer::LocalServer()
	: run(true), mMaxSocket(0)
{}

LocalServer::~LocalServer()
{
    mDirectClient.clear();
    printColorized("Good Bye!", GREEN);
}

int LocalServer::setPassAndPort(const char *password, const char *port)
{
	executer.setPass(password);
	executer.setPort(port);
	return (SUCCESS);
}

void LocalServer::mRenewSocket(const int &socket)
{
    FD_SET(socket, &this->mReadSockets);
    if (mMaxSocket < socket)
        mMaxSocket = socket;
}

static SSL_CTX	*InitCTX()
{
	const SSL_METHOD *method;
	SSL_CTX *ctx;

	OpenSSL_add_all_algorithms();  /* load & register all cryptos, etc. */
	SSL_load_error_strings();   /* load all error messages */
	method = SSLv23_method();  /* create new server-method instance */
	ctx = SSL_CTX_new(method);   /* create new context from method */
	if ( ctx == NULL ) {
		ERR_print_errors_fp(stderr);
	}
	return ctx;
}

static void LoadCertificates(SSL_CTX *ctx, const char* CertFile, const char* KeyFile, bool serv)
{
	if (serv) {
		//New lines
		if (SSL_CTX_load_verify_locations(ctx, CertFile, KeyFile) != 1)
			ERR_print_errors_fp(stderr);

		if (SSL_CTX_set_default_verify_paths(ctx) != 1)
			ERR_print_errors_fp(stderr);
		//End new lines
	}
	/* set the local certificate from CertFile */
	if (SSL_CTX_use_certificate_file(ctx, CertFile, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		abort();
	}
	/* set the private key from KeyFile (may be the same as CertFile) */
	if (SSL_CTX_use_PrivateKey_file(ctx, KeyFile, SSL_FILETYPE_PEM) <= 0)
	{
		ERR_print_errors_fp(stderr);
		abort();
	}
	/* verify private key */
	if (!SSL_CTX_check_private_key(ctx))
	{
		ERR_print_errors_fp(stderr);
		abort();
	}
}

int LocalServer::mTlsInit()
{
	SSL_library_init();

	ctx = InitCTX();
	if (ctx == NULL)
		exit(0);
	LoadCertificates(ctx, executer.getCert(), executer.getKey(), true);
	return (SUCCESS);
}

int LocalServer::init(const bool tlsTurn)
{
	const char *port;
    int localSock;
    int flag = 1;
    struct addrinfo hints;
    struct addrinfo *addrInfo;
    struct addrinfo *addrInfoIter;

	if (tlsTurn)
		port = executer.getTlsPort().c_str();
	else
		port = executer.getPort();
    /*
	 * TLS SETTING
	 */
	if (std::string(port) == executer.getTlsPort())
	{
		mTlsInit();
		printColorized("Tls Initializing ...", GREEN);
	}
    memset(&hints, 0x00, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(NULL, port, &hints, &addrInfo) == FAIL) // localServer 127.0.0.1
    {
        freeaddrinfo(addrInfo);
        return printError("getaddrinfo() error in function: init() | file: localServerInit.cpp", RED);
    }
    for (addrInfoIter = addrInfo; addrInfoIter != NULL; addrInfoIter = addrInfoIter->ai_next)
    {
        if (addrInfoIter->ai_family == AF_INET6)
        {
            if ((localSock = socket(addrInfoIter->ai_family, addrInfoIter->ai_socktype, addrInfoIter->ai_protocol)) == FAIL)
            {
                freeaddrinfo(addrInfo);
                return (printError("Can't open socket in function: init() | file: localServerInit.cpp", RED));
            }
            if (setsockopt(localSock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) == FAIL)
                return printError("Can't set socket options in function: setsockopt() | file: localServerInit.cpp", RED);
            if (bind(localSock, addrInfoIter->ai_addr, addrInfoIter->ai_addrlen) == FAIL)
                return printError("Can't bind socket in function: init() | file: localServerInit.cpp", RED);
            if (listen(localSock, SOMAXCONN) == FAIL)
                return printError("Can't listen socket in function: init() | file: localServerInit.cpp", RED);
        }
    }
    mRenewSocket(localSock);
    if (std::string(port) != executer.getTlsPort())
    {
        mNormalSocket = localSock;
        init(true);
    }
    else
        mTlsSocket = localSock;
    freeaddrinfo(addrInfo);
    return (SUCCESS);
}

int LocalServer::start(void)
{
	struct timeval timeout;
	std::set<int>::iterator next;
	std::set<int>::iterator curr;

	timeout.tv_sec = 2;
	timeout.tv_usec = 0;
	while(run)
	{
		FD_SET(this->mNormalSocket, &mReadSockets);
		FD_SET(this->mTlsSocket, &mReadSockets);
		curr = mDirectClient.begin();
		next = mDirectClient.begin();
		if (!mDirectClient.empty())
			++next;
		while (curr != mDirectClient.end())
		{
			// isDeletedClient = false;
			// if (it->second.getStatus() != UNKNOWN && it->second.getWaitPong() && it->second.getLastPing() >= PING_CYCLE)
			// {
			// 	it->second.setWaitPong(false);
			// 	sendMessage(Message(""
			// 		, "PING"
			// 		, this->prefix)
			// 		, &it->second);
			// 	it->second.setPingLimit(std::time(NULL));
			// }
			// if (!it->second.getWaitPong() && it->second.getPingLimit() > PING_LIMIT)
			// {
			// 	this->disconnectClient(Message(":" + it->second.getInfo(1)
			// 		, TIMEOUT // timeout
			// 		, it->second.getInfo(1)
			// 		  + " :ERROR: ping timeout"), &it->second);
			// 	if (this->mDirectClient.empty())
			// 		break;
			// 	isDeletedClient = true;
			// 	it = next;
			// 	// user를 삭제하는 경우에 다른 서버로 quit이 전송 안됨.
			// }
			// if (!isDeletedClient)
			// {
				FD_SET(*curr, &mReadSockets);
				if (next != mDirectClient.end())
					++next;
				++curr;
			// }
		}
		if (select(this->mMaxSocket + 1, &this->mReadSockets, NULL, NULL, &timeout) == FAIL)
			return (printError("Select fail in function start() | file: localServerInit.cpp", RED));
		curr = mDirectClient.begin();
		for (int listenFd = this->mNormalSocket; listenFd <= this->mMaxSocket;)
		{
			if (FD_ISSET(listenFd, &this->mReadSockets))
			{
				if (listenFd == this->mNormalSocket || listenFd == this->mTlsSocket)
					mAcceptClient(listenFd);
				else
				{
                    mSSLClient = false;
                    if (mSSLSocket.count(listenFd))
                        mSSLClient = true;
					mReceiveMessage(listenFd);
				}
			}
			if ((!this->mDirectClient.empty() && curr == mDirectClient.end()) || !run)
				break;
			if (listenFd < this->mTlsSocket)
				++listenFd;
			else if (mDirectClient.empty())
				break;
			else
			{
				listenFd = *curr;
				++curr;
			}
		}
	}
	SSL_CTX_free(ctx);
	return (SUCCESS);
}
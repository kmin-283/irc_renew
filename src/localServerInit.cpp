#include "LocalServer.hpp"

LocalServer::LocalServer(const char *password, const char *port)
    : pass(std::string(password)), port(std::string(port)), maxSocket(0)
{
}

LocalServer::~LocalServer()
{
    printColorized("Good Bye!", GREEN);
}

void	LocalServer::renewSocket(const int &socket)
{
	FD_SET(socket, &this->readSockets);
	if (maxSocket < socket)
		maxSocket = socket;
}

int LocalServer::init(const char *hostname, const char *port)
{
    int localSock;
    int flag = 1;
    struct addrinfo hints;
    struct addrinfo *addrInfo;
    struct addrinfo *addrInfoIter;

    /*
	 * TLS SETTING
	 */
    // if (std::string(port) == tlsPort) {
    // 	std::cout << "tls setting start..." << port << std::endl;
    // 	char CertFile[] = "ft_irc.pem";
    // 	char KeyFile[] = "ft_irc_key.pem";

    // 	SSL_library_init();
    // 	SSL_load_error_strings();

    // 	this->ctx = InitCTX();
    // 	if (this->ctx == NULL)
    // 		exit(0);
    // 	LoadCertificates(this->ctx, CertFile, KeyFile, true);
    // }

    memset(&hints, 0x00, sizeof(struct addrinfo));
    hints.ai_flags = AI_PASSIVE;
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    if (getaddrinfo(hostname, port, &hints, &addrInfo) != SUCCESS)
        return printError("getaddrinfo() error in function: init() | file: LocalServer.cpp", RED);
    for (addrInfoIter = addrInfo; addrInfoIter != NULL; addrInfoIter = addrInfoIter->ai_next)
    {
        if (addrInfoIter->ai_family == AF_INET6)
        {
            if ((localSock = socket(addrInfoIter->ai_family, addrInfoIter->ai_socktype, addrInfoIter->ai_protocol)) != SUCCESS)
                return printError("Can't open socket in function: init() | file: LocalServer.cpp", RED);
            if (setsockopt(localSock, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(flag)) != SUCCESS)
                return printError("Can't set socket options in function: setsockopt() | file: LocalServer.cpp", RED);
            if (bind(localSock, addrInfoIter->ai_addr, addrInfoIter->ai_addrlen) != SUCCESS)
                return printError("Can't bind socket in function: init() | file: LocalServer.cpp", RED);
            if (listen(localSock, SOMAXCONN) != SUCCESS)
                return printError("Can't listen socket in function: init() | file: LocalServer.cpp", RED);
        }
    }
    renewSocket(localSock);
    if (std::string(port) != tlsPort)
    {
        normalSocket = localSock;
        init(hostname, tlsPort.c_str());
    }
    else
        tlsSocket = localSock;
    freeaddrinfo(addrInfo);
    return (SUCCESS);
}
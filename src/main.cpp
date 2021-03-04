#include "LocalServer.hpp"

int main(int argc, char *argv[])
{
    LocalServer *localServer;
    const int remoteServerIndex = 1;
    const int portIndex = argc - 2;
    const int passIndex = argc - 1;

    if (argc > 4)
        return printError("There are too many arguments in function: main() | file: main.cpp", RED);
    if (argc == 2)
        return printError("command  in function: main() | file: main.cpp", RED);
    if (argc != 1 && !isValidPort(std::string(argv[portIndex])))
        return printError("Port must be numeric in function: main() | file: main.cpp", RED);
    localServer = new LocalServer();
    if (argc != 1)
        localServer->setPassAndPort(argv[passIndex], argv[portIndex]);
    if (localServer->init() != SUCCESS)
        return (FAIL);
    if (argc == 4)
        localServer->connectRemoteServer(argv[remoteServerIndex]);
    localServer->start();
    delete localServer;
    return (0);
}

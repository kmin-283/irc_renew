#include "LocalServer.hpp"

int main(int argc, char *argv[])
{
    char    *hostname;
    LocalServer *localServer;
    const int networkIndex = 1;
    const int portIndex = argc - 2;
    const int passIndex = argc - 1;

    if (argc > 4)
        return printError("There are too many arguments in function: main() | file: main.cpp", RED);
    else if (argc < 3)
        return printError("There are too few arguments in function: main() | file: main.cpp", RED);
    else if (!isValidPort(std::string(argv[portIndex])))
        return printError("Port must be numeric in function: main() | file: main.cpp", RED);
    else 
    {
        localServer = new LocalServer(argv[passIndex], argv[portIndex]);
        // if (localServer->init(hostname, argv[portIndex]) != SUCCESS)
            // return (FAIL);
        // if (argc == 4)
        //     localServer->connectRemoteServer(argv[networkIndex]);
        // localServer->start();
        delete localServer;
    }
    return (0);
}

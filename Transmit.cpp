#include "Transmit.hpp"

Transmit::Transmit()
{
}

Transmit::~Transmit()
{
    printColorized("Now network is clear.", GREEN);
}

// int Transmit::sendMsg(const Message &msg, const User *user)
// {
//     // user객체 안에 있는 kbyte주고받은 내용 증가.
//     std::string error;

//     error.append("Can't send message ");
//     error.append(msg.getTotalMessage());
//     if (send(user->getFd(), msg.getTotalMessage().c_str(), msg.getTotalMessage().length(), 0) == FAIL)
//         return printError(error.c_str(), RED);
//     return (SUCCESS);
// }

// int Transmit::sendMsg(const Message &msg, const RemoteServer *rServ)
// {
//     // remoteServer객체 안에 있는 kbyte주고받은 내용 증가.
//     // if (client->getFd() == this->sslFd)
//     // {
//     // 	if (ERROR == SSL_write(this->ssl, message.getTotalMessage().c_str(), message.getTotalMessage().length()))
//     // 		std::cerr << ERROR_SEND_FAIL << std::endl;
//     // }
//     // else
//     // {
//     std::string error;

//     error.append("Can't send message ");
//     error.append(msg.getTotalMessage());
//     if (send(rServ->getFd(), msg.getTotalMessage().c_str(), msg.getTotalMessage().length(), 0) == FAIL)
//         return printError(error.c_str(), RED);
//     return (SUCCESS);
//     // }
// }

int Transmit::sendMsg(const Message &msg, const int &clientId)
{
    std::string error;

    error.append("Can't send message ");
    error.append(msg.getTotalMessage());
    if (send(clientId, msg.getTotalMessage().c_str(), msg.getTotalMessage().length(), 0) == FAIL)
        return printError(error.c_str(), RED);
    return (SUCCESS);
}

void Transmit::broadcastMsg(const Message &msg, const RemoteServer *rServ)
{
    std::map<std::string, IClient *>::iterator iterator;

    for (iterator = this->mDirectServ.begin(); iterator != this->mDirectServ.end(); ++iterator)
    {
        if (static_cast<RemoteServer *>(iterator->second) != rServ)
            sendMsg(msg, iterator->second->getFd());
    }
}

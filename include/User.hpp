#ifndef USER_HPP
#define USER_HPP

#include "IClient.hpp"
#include "Channel.hpp"

class User: public IClient
{
private:
public:
    User(const int &clientId);
    User(const IClient *otherUser);
    virtual const std::string &getInfo(const int &idx) const;
    virtual ~User();
};

#endif
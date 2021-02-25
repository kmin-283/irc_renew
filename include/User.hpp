#ifndef USER_HPP
#define USER_HPP
#include "IClient.hpp"
#include "Message.hpp"

class User: public IClient
{
private:
    /* data */
public:
    User(/* args */);
    virtual std::string &getInfo(const int &idx);
    virtual ~User();
};

#endif
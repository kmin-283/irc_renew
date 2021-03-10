#ifndef ICLIENT_HPP
#define ICLIENT_HPP

#include "utils.hpp"

class IClient
{
protected:
    int mClientId;
    int sendKbyte;
    int recvKbyte;
    std::vector<std::string> mInfos;
public:
    virtual const std::string &getInfo(const int &idx) const = 0;
    const int getClientId() const
    {
        return this->mClientId;
    }
    void setValue(const int &idx, const std::string &value)
    {
        mInfos[idx] = value;
    }
    virtual ~IClient() {}
};
#endif
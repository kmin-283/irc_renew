#ifndef VARIABLES_HPP
#define VARIABLES_HPP

#include "utils.hpp"

struct vGlobal
{
    std::string mName;
    std::string mInfo;
    std::string mPass;
    std::string mPort;
};

// struct vLimits
// {

// };

// struct vChannel
// {

// };


// struct vSSL
// {
//     std::string mPort;
// };

struct vServer
{
    std::string mName;
    std::string mMyPass;
    std::string mPeerPass;
};

class Variables
{
public:
    vGlobal global;
    size_t serversIdx;
    std::vector<vServer> servers;
    Variables();
    ~Variables();
    int setKey(vGlobal &global, char *buf);
    int setKey(vServer &server, char *buf);
};

#endif
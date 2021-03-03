#include "utils.hpp"

int printColorized(const char *msg, const char *color)
{
    std::cout << color << msg << COLOR_SUFFIX << std::endl;
    return (SUCCESS);
}

int printError(const char *error, const char *color)
{
    std::cerr << color << error << COLOR_SUFFIX << std::endl;
    return (FAIL);
}

bool isCoincide(const std::string &mask, const char &target)
{
    return (mask.find(target) != std::string::npos);
}

static bool pointCheck(const int &idx, const char next)
{
    if (idx == 0 || next == '.' || next == 0)
        return (false);
    return (true);
}

bool isValidIp(const std::string &ip)
{
    // ip 주소일 수도 있고, 혹은 www.google.com 일 수도 있음
    size_t ipLength;
    int hasPoint;

    ipLength = ip.length();
    hasPoint = 0;
    if (!ipLength)
        return (false);
    if (isdigit(ip[0])) // 127.0.0.1
    {
        for (size_t i = 0; i < ipLength; ++i)
        {
            if (isdigit(ip[i]))
                continue;
            if (ip[i] == '.')
            {
                if (!pointCheck(i, ip[i+1]))
                    return (false);
                hasPoint += 1;
            }
            else
                return (false);
        }
        return (hasPoint == 3 ? true : false);
    }
    return (true);
    // else // www.google.com
    // {
    //     for (size_t i = 0; i < ipLength; ++i)
    //     {
    //         if (isalpha(ip[i]))
    //             continue;
    //         if (ip[i] == '.')
    //         {
    //             if (!pointCheck(i, ip[i+1]))
    //                 return (false);
    //             hasPoint += 1;
    //         }
    //         else
    //             return (false);
    //     }
    //     return (hasPoint == 2? true : false);
    // }
}

bool isValidPort(const std::string &port)
{
    size_t portLength;

    portLength = port.length();
    if (portLength == 0)
        return (false);
    for (size_t i = 0; i < portLength; ++i)
    {
        if (!isdigit(port[i]))
            return (false);
    }
    return (true);
}

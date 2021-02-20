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

bool isValidPort(const std::string &port)
{
    size_t portLength;

    portLength = port.length();
    if (portLength == 0)
        return (false);
    for (size_t i = 0; i < portLength; ++i)
    {
        if (!isCoincide(std::string(DIGIT), port[i]))
            return (false);
    }
    return (true);
}
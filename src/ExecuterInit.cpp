#include "Executer.hpp"

template<typename _Category>
int Executer::mSetCategory(_Category &category, std::ifstream &f)
{
    char buf[256];

    f.getline(buf, 256);
    while (!f.eof() && buf[0] != '[')
    {
        if (buf[0] != 0)
            var.setKey(category, buf);
        f.getline(buf, 256);
    }
    if (buf[0] == '[')
    {
        int len = strlen(buf) + 1;
        long pos = f.tellg();
        f.seekg(pos - len);
    }
    return (SUCCESS);
}

int Executer::mSearchCategory(std::ifstream &f, const char *category)
{
    switch (djb2_hash(category))
    {
    case djb2_hash("[Global]"):
        mSetCategory(var.global, f);
        break;
    case djb2_hash("[SSL]"):
        mSetCategory(var.ssl, f);
        break;
    case djb2_hash("[Server]"):
        mSetCategory(var.servers[var.serversIdx], f);
        ++var.serversIdx;
        break;
    case djb2_hash("[Limits]"):
        mSetCategory(var.limits, f);
    default:
        break;
    }
    return (SUCCESS);
}

int Executer::mInitFromConf()
{
    std::ifstream f("./myirc.conf");
    char inputString[256];

    while (!f.eof())
    {
        f.getline(inputString, 256);
        if (inputString[0] == '[')
            mSearchCategory(f, inputString);
    }
    f.close();
    return (SUCCESS);
}
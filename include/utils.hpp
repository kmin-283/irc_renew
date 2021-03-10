#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include <cctype>
#include <sstream>
#include <fstream>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <vector>

#include <cstdio>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include <cstring>
#include <string.h>

#include "macros.hpp"

int printColorized(const char *msg, const char *color);
int printError(const char *error, const char *color);
bool isCoincide(const std::string &mask, const char &target);
bool isValidIp(const std::string &ip);
bool isValidPort(const std::string &port);
constexpr unsigned long djb2_hash_impl(const char *text, unsigned long prev_hash)
{
    return text[0] == '\0' ? prev_hash : djb2_hash_impl( &text[1], prev_hash * 33 ^ static_cast<unsigned long>(text[0]) );
}
constexpr unsigned long djb2_hash(const char *text)
{
    return djb2_hash_impl( text, 5381 );
}


#endif
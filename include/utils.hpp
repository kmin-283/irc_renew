#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>
#include <iostream>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "string.h"

#include "macros.hpp"

int printColorized(const char *msg, const char *color);
int printError(const char *error, const char *color);
bool isCoincide(const std::string &mask, const char &target);
bool isValidPort(const std::string &port);


#endif
#ifndef MACROS_HPP
#define MACROS_HPP
/*
 * colors
 */
#define RED "\033[1;31m"
#define GREEN "\033[1;32m"

#define COLOR_SUFFIX "\033[0m\n"
/*
 * connection
 */
#define CONN 1
#define DISCONN 0

#define SUCCESS 0
#define FAIL -1
/*
 * message
 */
#define CR_LF "\r\n"
/*
 * debug
 */
#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif

enum CMD
{
    /*
         * connection registration
         */
    PASS,
    NICK,
    USER,
    OPER,
    USERMODE,
    // SERVICE,
    QUIT,
    SQUIT,
    /*
         * channel operation
         */
    JOIN,
    PART,
    CHANNELMODE,
    TOPIC,
    NAMES,
    LIST,
    INVITE,
    KICK,
    /*
         * sending messages
         */
    PRIVMSG,
    NOTICE,
    /*
         * server queries and commands
         */
    // MOTD,
    // LUSER,
    VERSION,
    STATS,
    LINKS,
    TIME,
    CONNECT,
    TRACE,
    ADMIN,
    INFO,
    /*
         * service query and commands
         */
    // SERVLIST,
    // SQUERY,
    /*
         * user based queries
         */
    // WHO,
    // WHOIS,
    /*
         * miscellaneous message
         */
    // KILL,
    PING,
    PONG,
    // ERROR,
    /*
         * optional feature
         */
    // AWAY,
    // REHASH,
    // DIE,
    // RESTART,
    // SUMMON,
    // USERS,
    // OPERWALL,
    // USERHOST,
    // ISON,
};
#endif
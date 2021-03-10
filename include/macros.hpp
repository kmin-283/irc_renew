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
#define CONN 0
#define DISCONN -1
#define ERASE_SERVER -2
#define NOT_FOUND -3
#define IGNORE -4
/*
 * register
 */
#define REGISTERED 1
#define NOT_REGISTERED 0
/*
 * mask
 */
#define DIGIT "0123456789"
#define SPECIAL "-[]\\`^{|}"
#define LETTER "abcdefghijklmnopqrstuvwxyzABCDEFGHJKLMNOPQRSTUVWYZ"
/*
 * message
 */
#define CR_LF "\r\n"
/*
 * auth bit
 */
#define AUTH_PASS 1
#define AUTH_NICK 2
#define AUTH_BROADCAST 256
/*
 * debug
 */
#ifdef DEBUG
#define DEBUG 1
#else
#define DEBUG 0
#endif
/*
 * etc
 */
#define SUCCESS 0
#define FAIL -1
#define ERR_REPLY 400

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

/*
 * user infos
 */
enum USER_INFO
{
     UI_HOSTNAME,
	UI_NICK,
	UI_ADDRESS,
	UI_USERNAME,
	UI_REALNAME,
	UI_USERMODE
};

/*
 * replies
 */



/*
 * err replies
 */
#define ERR_NONICKNAMEGIVEN "431"
#define ERR_ERRONEUSNICKNAME "432"
#define ERR_NICKNAMEINUSE "433"
#define ERR_NICKCOLLISION "436"


#define ERR_NEEDMOREPARAM "461"
#define ERR_ALREADYREGISTRED "462"


#define ERR_NOTAUTHORIZED "503"
#endif
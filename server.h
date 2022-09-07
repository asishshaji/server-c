#ifndef SERVER_H
#define SERVER_H

#include <sys/socket.h>
#include <netinet/in.h>

struct Server
{
    int domain;
    int protocol;
    int service;
    u_long interface;
    int port;
    int backlog;

    struct sockaddr_in address;

    int socket;

    void (*launch)(void);
};

struct Server init_server(int domain, int protocol, int service, u_long interface,
                          int port, int backlog, void (*launch)(void));

#endif // !SERVER_H
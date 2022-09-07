#include "server.h"
#include <stdlib.h>
#include <stdio.h>

struct Server init_server(int domain, int protocol, int service, u_long interface,
                          int port, int backlog, void (*launch)(void))
{
    struct Server server;

    server.domain = domain;
    server.protocol = protocol;
    server.service = service;
    server.interface = interface;
    server.port = port;
    server.backlog = backlog;
    server.launch = launch;

    server.address.sin_family = domain;
    server.address.sin_port = htons(port);
    server.address.sin_addr.s_addr = htonl(interface);

    server.socket = socket(domain, service, protocol);
    if (server.socket == 0)
    {
        perror("Failed to connect to socket\n");
        exit(1);
    }

    if ((bind(server.socket, (struct sockaddr *)&server.address,
              sizeof(server.address))) < 0)
    {
        perror("Failed to bind socket\n");
        exit(1);
    }

    if ((listen(server.socket, server.backlog)) < 0)
    {
        perror("Failed to listen\n");
        exit(1);
    }

    server.launch = launch;

    return server;
}
#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__

#include <netinet/in.h>

int tcp_server_connect(uint16_t port, int* server);

void close_connection(int socket);

void shutdown_server(int server_socket, int how);

#endif/*__TCP_SERVER_H__*/
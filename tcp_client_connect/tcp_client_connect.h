#ifndef __CLIENT_CONNECT_H__
#define __CLIENT_CONNECT_H__

#include <arpa/inet.h>

int tcp_client_connect(char* IP, uint16_t port);

void close_connection(int socket);

#endif /* __CLIENT_CONNECT_H__*/
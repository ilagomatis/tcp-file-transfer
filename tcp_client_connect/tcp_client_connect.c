#include "tcp_client_connect.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int tcp_client_connect(char* IP, uint16_t port)
{
    int status, client_socket;
    struct sockaddr_in serv_addr;

    if ((client_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        return -1;
    
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(port);

    if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) 
        return -1;

    status = connect(client_socket, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
    if(status < 0)    
        return -1;

    return client_socket;
}

void close_connection(int socket)
{
    close(socket);
}
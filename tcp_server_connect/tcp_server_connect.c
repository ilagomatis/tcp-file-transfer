#include "tcp_server_connect.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int tcp_server_connect(uint16_t port, int* server)
{
    int server_socket, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if(server_socket < 0)
        exit(EXIT_FAILURE);
    
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt)))
        exit(EXIT_FAILURE);
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_socket, (struct sockaddr*)&address, sizeof(address)) < 0) 
        exit(EXIT_FAILURE);
    
    if (listen(server_socket, 3) < 0)
        exit(EXIT_FAILURE);
    
    new_socket = accept(server_socket, (struct sockaddr*)&address, (socklen_t*)&addrlen);
    if (new_socket < 0) 
        exit(EXIT_FAILURE);
    
    *server = server_socket;
    return new_socket;
}

void close_connection(int socket)
{
    close(socket);
}

void shutdown_server(int server_socket, int how)
{
    shutdown(server_socket, how);
}
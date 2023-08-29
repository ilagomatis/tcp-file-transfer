#include"send_file.h"
#include"../tcp_client_connect/tcp_client_connect.h"
#include"../string_utils/string_utils.h"
#include"../packet/packet.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define FIRST_MSG_SZ 100
#define SEPARATOR "-"

int sendfile(char* IP, uint16_t port, char* pathtofile, int chunksize){
    int sock;
    int bytes;
    
    unsigned char* content = getBinaryContent(pathtofile, &bytes);
    struct message* message = buildMessage(content, bytes, chunksize);
    free(content);
    for(int i=0; i<message->size; i++)
    {
        printf("packet %d: %d bytes\n", i+1, message->packets[i].size);
    }
    
    char* metadata = joinPacketSizes(message, SEPARATOR);
    int metadatasize = strlen(metadata);
    printf("metadataSize: %d\n", metadatasize);
    printf("%s\n", metadata);
    char* firstmessage = (char*)malloc(FIRST_MSG_SZ * sizeof(char));
    sprintf(firstmessage, "%d", metadatasize);

    sock = tcp_client_connect(IP, port);

    send(sock, firstmessage, FIRST_MSG_SZ, 0);
    send(sock, metadata, metadatasize, 0);

    for(int i=0; i<message->size; ++i)
    {
        send(sock, message->packets[i].data, message->packets[i].size, 0);
    }

    // read the response

    close_connection(sock);
    freeMessage(message);
    free(firstmessage);
    return 0;
}

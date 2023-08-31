#include"send_file.h"
#include"../tcp_client_connect/tcp_client_connect.h"
#include"../string_utils/string_utils.h"
#include"../packet/packet.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define FIRST_MSG_SZ 100
#define SEPARATOR "-"

int sendfile(char* IP, uint16_t port, char* pathtofile, int chunksize){
    int sock;
    int bytes;
    clock_t start, end;
    double cpu_time_used;
    
    start = clock();
    unsigned char* content = getBinaryContent(pathtofile, &bytes);
    struct message* message = buildMessage(content, bytes, chunksize);
    
    free(content);
    
    char* metadata = joinPacketSizes(message, SEPARATOR);
    int metadatasize = strlen(metadata);
    //printf("metadataSize: %d\n", metadatasize);
    //printf("%s\n", metadata);
    char* firstmessage = (char*)malloc(FIRST_MSG_SZ * sizeof(char));
    sprintf(firstmessage, "%d", metadatasize);

    sock = tcp_client_connect(IP, port);

    send(sock, firstmessage, FIRST_MSG_SZ, 0);
    //printf("Bytes sent: %d\n", FIRST_MSG_SZ);

    send(sock, metadata, metadatasize, 0);
    //printf("Bytes sent: %d\n", metadatasize);

    for(int i=0; i<message->size; ++i)
    {
        char buf = '1';
        int status = send(sock, (unsigned char *)message->packets[i].data, message->packets[i].size, 0);
        printf("status for %d: %d\n", i, status);
        read(sock, &buf, 1);
        //printf("packet %d: %d bytes first char: %u last char: %u\n", i+1, message->packets[i].size, message->packets[i].data[0], message->packets[i].data[message->packets[i].size -1]);
    }

    // read the response
    char* resp = (char*)malloc(1000);
    read(sock, resp, 1000);
    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("Time for response: %f\n", cpu_time_used);
    printf("Response: \n%s\n", resp);
    close_connection(sock);
    freeMessage(message);
    free(firstmessage);
    free(resp);
    return 0;
}

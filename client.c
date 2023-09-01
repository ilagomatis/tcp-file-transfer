#include "clientproto/send_file.h"
#include "packet/packet.h"
#include "string_utils/string_utils.h"
#include "tcp_client_connect/tcp_client_connect.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define PORT 8080
#define FILENAME "../string/cat.rgb"
#define CHUNK 1000
#define MAXCHUNK 100000
#define IP "192.168.100.2"//"10.64.83.226"

int main(int argc, char **argv)
{
    
    if(argc < 3)
    {
        printf("Insert at least two args: ./client.out <IP> <FILE> (<CHUNKSIZE>)\n");
        exit(0);
    }

    int chunksize;
    if(argc == 3){
        printf("IP: %s\nPATH: %s\n", argv[1], argv[2]);
        chunksize = CHUNK;
    }
    if(argc >= 4)
    {
        printf("IP: %s\nPATH: %s\n", argv[1], argv[2]);
        int chunkarg = atoi(argv[3]);
        chunksize = (chunkarg > MAXCHUNK) ? MAXCHUNK : chunkarg;
        printf("CHUNK: %d\n", chunksize);
    }

    sendfile(argv[1], PORT, argv[2], chunksize);
}
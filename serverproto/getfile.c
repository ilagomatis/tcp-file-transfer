#include "getfile.h"

#include "../tcp_server_connect/tcp_server_connect.h"
#include "../string_utils/string_utils.h"

#include <stdlib.h>
#include <stdio.h>

#define FIRST_MSG_SZ 100
#define SEPARATOR "-"
#define FILENAME "copy"

int readContent(int socket, char** packetSizes, int numPackets, char* file)
{
	FILE* fd = fopen(file, "wb");

	for(int i=0; i<numPackets; i++)
	{
		int bytes = atoi(packetSizes[i]);
		unsigned char* buf = (unsigned char*) malloc(sizeof(unsigned char) * bytes);
		int valread = read(socket, buf, bytes);
		//printf("Packet %d bytes: %d first char:%u last char:%u\n", i+1, bytes, buf[0], buf[bytes-1]);
		fwrite(buf, bytes, 1, fd);
		free(buf);
	}

	fclose(fd);
}


int getfile(uint16_t port)
{
    int server;
    int valread;

    char* firstmsg = (char*)malloc(FIRST_MSG_SZ * sizeof(char));
    int client = tcp_server_connect(port, &server); // block until new connection

    valread = read(client, firstmsg, FIRST_MSG_SZ);

    int metadataSize = atoi(firstmsg);
    free(firstmsg);

    char* metadata = (char*)malloc(metadataSize * sizeof(char));
    valread = read(client, metadata, metadataSize);

    int numPackets;
    char** packetSizes = split(metadata, SEPARATOR, &numPackets);
    free(metadata);
    
    readContent(client, packetSizes, numPackets, FILENAME);

    freeSplitRes(packetSizes, numPackets);
    

    close_connection(client);
    shutdown_server(server, SHUT_RDWR);
}

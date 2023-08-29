#include "packet.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct packet* buildPackets(int packetsize, int filesize, int* numPackets)
{
    int numpackets = 0;
    struct packet* packets = (struct packet*)malloc(0);
    
    for(int i=packetsize; i<(filesize + packetsize); i+=packetsize)
    {
        packets = realloc(packets, sizeof(struct packet)*(++numpackets));
        packets[numpackets - 1].size = (i<filesize) ? packetsize : (packetsize - (i - filesize));
    }

    *numPackets = numpackets;
    return packets; 
} 

struct message* buildMessage(unsigned char* filebuf, int filesize, int packetsize)
{
    struct message* msg;

    if(filebuf == NULL || !filesize || !packetsize) return NULL;
    msg = (struct message*) malloc(sizeof(struct message));
    msg->packets = buildPackets(packetsize, filesize, &msg->size);

    int buffptr = 0; 
    for(int i=0; i<msg->size; i++)
    {
        msg->packets[i].data = (unsigned char*)malloc(msg->packets[i].size * sizeof(unsigned char));
        memcpy(msg->packets[i].data, &filebuf[buffptr], msg->packets[i].size);
        buffptr += msg->packets[i].size;
    }
    return msg;
}

int getMetadataSize(struct message msg)
{
    char* intbuf = (char*)malloc(10 * sizeof(char));
    int len = 0;
    for(int i=0; i<msg.size; i++)
    {
        memset(intbuf, '\0', 10);
        sprintf(intbuf, "%d", msg.packets[i].size);
        int numberLen = strlen(intbuf);
        len += numberLen;
        len++;
    }
    free(intbuf);
    printf("len: %d\n", --len);
    return (len - 1);
}

char* joinPacketSizes(struct message* msg, char *separator)
{
    int len = getMetadataSize(*msg);
    char* out = (char*) malloc(sizeof(char) * len);
    char* intbuf = (char*) malloc(sizeof(char) * 10);
    sprintf(intbuf, "%d", msg->packets[0].size);
    strcpy(out, intbuf);
    for(int i=0; i<(msg->size - 1); i++)
    {
        strcat(out, separator);
        memset(intbuf, '\0', 10);
        sprintf(intbuf, "%d", msg->packets[i+1].size);
        strcat(out, intbuf);
    }
    strcat(out, "\0");
    return out;
}

int freeMessage(struct message* msg)
{
    if(msg == NULL) 
        return -1;

    for(int i=0; i<msg->size; i++)
    {
        if(msg->packets[i].data == NULL) 
            return -1;

        free(msg->packets[i].data);
        msg->packets[i].size = 0;
    }

    free(msg);
    return 0;
}
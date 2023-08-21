#include "packet.h"
#include <stdlib.h>
#include <string.h>
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

char* joinPacketSizes(struct message* msg, char *separator)
{
    char* out = (char*) malloc(sizeof(char) * 1000);
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

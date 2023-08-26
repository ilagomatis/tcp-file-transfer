#ifndef __PACKET_H__
#define __PACKET_H__

struct packet
{
    unsigned char* data;
    int size;
};

struct message
{
    struct packet* packets;
    int size;
};

struct message* buildMessage(unsigned char* filebuf, int filesize, int packetsize);

char* joinPacketSizes(struct message* msg, char *separator);

int freeMessage(struct message* msg);

#endif /* __PACKET_H__ */
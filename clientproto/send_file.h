#ifndef __SEND_FILE_H__
#define __SEND_FILE_H__

#include <arpa/inet.h>

int sendfile(char* IP, uint16_t port, char* pathtofile, int chunksize);

#endif/*__SEND_FILE_H__*/
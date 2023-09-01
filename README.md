# tcp-file-transfer
A library written in C with functions that may help you send files remotely

![report](https://github.com/ilagomatis/tcp-file-transfer/assets/78209098/ce59a429-120b-43e6-b822-100a88b4279b)

Currently works with binary files, as the purpose i implemented that was to transfer binary imagies.


# How it works

## Client:

1. reads the user input: IP, PATH-TO-FILE, CHUNKSIZE,
2. reads the file and breaks it into chunks,
3. creates a connection with the server on the given IP,
4. follows a protocol to inform the server about the packets that's about to receive,
5. sends all the packets one after the other to the server. After every packet waits for an ok-response,
6. closes the conection and returns.

## Server:

1. waits for connections,
2. after client connected, the server waits for the metadata,
3. extracts information about the metadata (filesize, number of packets),
4. creates a file
5. receives all the packets and sends an ok-response for each one,
6. after receiving each packet, appends the data inside the file
7. closes the connection, terminates the server and returns


# Build & Run

## Server

```
make server
./server.out
```

## Client

```
make client
./client.out <IP> <PATH_TO_BIN_FILE> <CHUNKSIZE(optional)>
# e.g. ./client.out 192.168.100.2 /home/user/Documents/img.rgb
```

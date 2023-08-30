# tcp-file-transfer
A library written in C with functions that may help you send files remotely

![report](https://github.com/ilagomatis/tcp-file-transfer/assets/78209098/ce59a429-120b-43e6-b822-100a88b4279b)

Currently works with binary files, as the purpose i implemented that was to transfer binary imagies

# Server

```
make server
./server.out
```

# Client

```
make client
./client.out <IP> <PATH_TO_BIN_FILE> <CHUNKSIZE(optional)>
# e.g. ./client.out 192.168.100.2 /home/user/Documents/img.rgb
```

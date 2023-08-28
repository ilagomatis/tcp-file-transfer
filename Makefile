all: tcp_server_connect/tcp_server_connect.o
	gcc server.c -o server tcp_server_connect/tcp_server_connect.o
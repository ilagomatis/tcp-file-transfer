server: string_utils/string_utils.o \
		tcp_server_connect/tcp_server_connect.o \
		serverproto/getfile.o
	gcc server.c -o server.out string_utils/string_utils.o \
					tcp_server_connect/tcp_server_connect.o \
					serverproto/getfile.o

client: string_utils/string_utils.o \
		packet/packet.o \
		tcp_client_connect/tcp_client_connect.o \
		clientproto/send_file.o
	gcc client.c -o client.out string_utils/string_utils.o \
							   packet/packet.o \
							   tcp_client_connect/tcp_client_connect.o \
							   clientproto/send_file.o
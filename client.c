#include "clientproto/send_file.h"
#include "packet/packet.h"
#include "string_utils/string_utils.h"
#include "tcp_client_connect/tcp_client_connect.h"

#define PORT 8080
#define FILENAME "../string/cat.rgb"
#define CHUNK 250
#define IP "127.0.0.1"//"10.64.83.216"

int main(){
    sendfile(IP, PORT, FILENAME, CHUNK);
}
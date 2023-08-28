#include "clientproto/send_file.h"
#include "packet/packet.h"
#include "string_utils/string_utils.h"
#include "tcp_client_connect/tcp_client_connect.h"
int main(){
    sendfile("asd", 1000, "../string/cat.rgb", 1000);
}
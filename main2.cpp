#include <iostream>
#include "my_cpp_network_lib/cpp_network_inc.h"
#include "my_cpp_network_lib/My_client.h"
#include "my_cpp_network_lib/My_server.h"

int main(int, char **)
{
    My_client my_client;
    char      buffer[1024];
    sprintf(buffer, "你好，世界");
    int i = 0;
    my_client.create_client_socket();
    my_client.request_to_connect_server("127.0.0.1", "9999");
    while (i < 15) {
        if (my_client.send_msg_to_server(buffer) == -1) {
            break;
        }
        sleep(1);
        i++;
    }
    my_client.close_client_socket();
    return 0;
}

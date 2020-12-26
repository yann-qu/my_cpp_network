#include <iostream>
#include "my_cpp_network_lib/cpp_network_inc.h"
#include "my_cpp_network_lib/My_client.h"
#include "my_cpp_network_lib/My_server.h"

int main(int, char **)
{
    My_server my_server;
    char      buffer[1024];
    my_server.create_server_socket();
    my_server.config_server("127.0.0.1", "9999");
    my_server.acpt_client_connect();
    while (my_server.recv_msg_from_client(buffer, sizeof(buffer)) == 1) {
        std::cout << "接收：" << buffer << std::endl;
        my_server.send_msg_to_client("ok");
        std::cout << "发送："
                  << "ok" << std::endl;
    }
    my_server.close_server_socket();
    return 0;
}

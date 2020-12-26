#include <iostream>
#include "my_cpp_network_lib/cpp_network_inc.h"
#include "my_cpp_network_lib/My_client.h"
#include "my_cpp_network_lib/My_server.h"

int main(int, char **)
{
    My_client my_client;
    char      send_buffer[1024];
    char      recv_buffer[1024];
    sprintf(send_buffer, "你好，世界");
    int  i = 0;
    bool flag;
    my_client.create_client_socket();
    my_client.request_to_connect_server("127.0.0.1", "9999");
    while (i < 15) {
        flag = my_client.send_msg_to_server(send_buffer);
        if (flag == 1) {
            std::cout << "发送：" << send_buffer << std::endl;
            my_client.recv_msg_from_server(recv_buffer, sizeof(recv_buffer));
            std::cout << "接收：" << recv_buffer << std::endl;
        } else {
            break;
        }
        sleep(1);
        i++;
    }
    my_client.close_client_socket();
    return 0;
}

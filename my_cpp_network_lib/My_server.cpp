#include "cpp_network_inc.h"
#include <iostream>
#include "My_server.h"

My_server::My_server(void)
{
    listenfd = 0;
    clientfd = 0;
}

/**
 * @Date: 2020-12-25 15:45:17
 * @description: 创建socket
 * @param void
 * @return void
 */
int My_server::create_server_socket(void)
{
    if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }
    return 1;
}

/**
 * @Date: 2020-12-25 15:33:35
 * @description: 配置服务器。完成：
 *     1.把服务端用于通信的地址和端口绑定到socket上。
 *     2.把socket设置为监听模式。
 * @param ip_addr:要监听的ip地址，为"0"时不限制
 * @param port:要监听的端口
 * @return 1:配置成功 -1:配置失败
 */
int My_server::config_server(const char *ip_addr, const char *port)
{
    // 把服务端用于通信的地址和端口绑定到socket上。
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    if (ip_addr == "0") {
        servaddr.sin_addr.s_addr = htonl(INADDR_ANY); // 任意ip地址。
    } else {
        servaddr.sin_addr.s_addr = inet_addr(ip_addr); // 指定ip地址。
    }
    servaddr.sin_port = htons(atoi(port));
    if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("bind");
        close(listenfd);
        return -1;
    }

    // 把socket设置为监听模式。
    if (listen(listenfd, 5) != 0) {
        perror("listen");
        close(listenfd);
        return -1;
    }

    return 1;
}

/**
 * @Date: 2020-12-25 16:04:11
 * @description: 接受客户端的连接
 * @param void
 * @return 1 -1
 */
int My_server::acpt_client_connect(void)
{
    int                socklen = sizeof(struct sockaddr_in);
    // int clientfd;
    // struct sockaddr_in clientaddr; //客户端的地址信息
    clientfd =
        accept(listenfd, (struct sockaddr *)&clientaddr, (socklen_t *)&socklen);
    if (clientfd == -1) {
        perror("accept");
        this->close_server_socket();
        return -1;
    }
    std::cout<<"客户端（"<<inet_ntoa(clientaddr.sin_addr)<<"）已连接。"<<std::endl;
    return 1;
}

/**
 * @Date: 2020-12-25 16:18:10
 * @description: 从客户端接收信息
 * @param buffer:接收缓冲区
 * @return 1 -1
 */
int My_server::recv_msg_from_client(char* buffer,size_t buffer_size)
{
    int iret;
    memset(buffer, 0, buffer_size);
    if ((iret = recv(clientfd, buffer, buffer_size, 0)) <= 0) {
        // 接收客户端的请求报文。
        std::cout<<"iret="<<iret<<std::endl;
        perror("receive");
        return -1;
    }
    return 1;
}

/**
 * @Date: 2020-12-25 16:16:01
 * @description: 向客户端发送信息
 * @param buffer:发送缓冲区
 * @return 1 -1
 */
int My_server::send_msg_to_client(const char *buffer)
{
    int iret;
    if ((iret = send(clientfd, buffer, strlen(buffer), 0)) <= 0)
    // 向客户端发送响应结果。
    {
        std::cout<<"iret="<<iret<<std::endl;
        perror("send");
        return -1;
    }
    return 1;
}

/**
 * @Date: 2020-12-25 16:23:30
 * @description: 关闭socket
 * @param void
 * @return void
 */
void My_server::close_server_socket(void)
{
    close(listenfd);
    close(clientfd);
}

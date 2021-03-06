#include "cpp_network_inc.h"
#include <iostream>
#include "My_client.h"

My_client::My_client(void)
{
    sockfd = 0;
}

/**
 * @Date: 2020-12-25 15:49:31
 * @description: 创建socket。
 * @param void
 * @return 1 -1
 */
int My_client::create_client_socket(void)
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        return -1;
    }
    return 1;
}

/**
 * @Date: 2020-12-25 15:50:09
 * @description: 向服务器发起连接请求。
 * @param _h host
 * @param _port port
 * @return
 */
int My_client::request_to_connect_server(const char *_h, const char *_port)
{
    if ((h = gethostbyname(_h)) == 0) {
        std::cout<<"gethostbyname failed."<<std::endl;
        close(sockfd);
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port   = htons(atoi(_port));
    memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0) {
        perror("connect");
        close(sockfd);
        return -1;
    }
    return 1;
}

/**
 * @Date: 2020-12-25 15:50:52
 * @description: 向服务器发送信息
 * @param _buffer 发送信息缓冲区
 * @return 1 -1
 */
int My_client::send_msg_to_server(const char *_buffer)
{
    int iret;
    if ((iret = send(sockfd, _buffer, strlen(_buffer), 0)) <= 0) {
        std::cout<<"iret="<<iret<<std::endl;
        perror("send");
        return -1;
    }
    return 1;
}

/**
 * @Date: 2020-12-25 15:51:19
 * @description: 从服务器接收信息
 * @param _buffer：接收信息缓冲区
 * @return 1 -1
 */
int My_client::recv_msg_from_server(char *_buffer,size_t _buffer_size)
{
    int iret;
    memset(_buffer, 0, _buffer_size);
    if ((iret = recv(sockfd, _buffer, _buffer_size, 0)) <= 0) {
        std::cout<<"iret="<<iret<<std::endl;
        perror("receive");
        return -1;
    }
    return 1;
}

/**
 * @Date: 2020-12-25 15:52:46
 * @description: 关闭socket。
 * @param void
 * @return void
 */
void My_client::close_client_socket(void)
{
    close(sockfd);
}

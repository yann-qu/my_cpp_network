#include "cpp_network_inc.h"
#include <iostream>
#include "My_client.h"

My_client::My_client(void)
{
    sockfd = 0;
    // memset(send_buffer, 0, sizeof(send_buffer));
    // memset(recv_buffer, 0, sizeof(recv_buffer));
}

/**
 * @Date: 2020-12-25 15:49:31
 * @description: 创建socket。
 * @param void
 * @return 1 -1
 */
int My_client::create_client_socket(void)
{
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
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
    if ((h = gethostbyname(_h)) == 0)
    {
        printf("gethostbyname failed.\n");
        close(sockfd);
        return -1;
    }
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(atoi(_port));
    memcpy(&servaddr.sin_addr, h->h_addr, h->h_length);
    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) != 0)
    {
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
    if ((iret = send(sockfd, _buffer, strlen(_buffer), 0)) <= 0)
    {
        printf("iret=%d\n", iret);
        perror("send");
        return -1;
    }
    std::cout<<strlen(_buffer)<<std::endl;
    return 1;
}

// int My_client::send_msg_to_server(void){
//     int iret;
//     if((iret=send(sockfd,send_buffer,strlen(send_buffer),0))<=0){
//         perror("send");
//         close(sockfd);
//         return -1;
//     }
//     printf("发送：%s",send_buffer);
//     memset(send_buffer, 0, sizeof(send_buffer)); //清空发送缓冲区
//     return 1;
// }

// int My_client::recv_msg_from_server(void){
//     int iret;
//     memset(recv_buffer,0,sizeof(recv_buffer));
//     if((iret=recv(sockfd,recv_buffer,sizeof(recv_buffer),0))<=0){
//         perror("receive");
//         close(sockfd);
//         return -1;
//     }
//     printf("接收：%s",recv_buffer);
//     return 1;
// }

/**
 * @Date: 2020-12-25 15:51:19
 * @description: 从服务器接收信息
 * @param _buffer：接收信息缓冲区
 * @return 1 -1
 */
int My_client::recv_msg_from_server(char *_buffer)
{
    int iret;
    memset(_buffer, 0, sizeof(_buffer));
    if ((iret = recv(sockfd, _buffer, sizeof(_buffer), 0)) <= 0)
    {
        printf("iret=%d\n", iret);
        perror("receive");
        close(sockfd);
        return -1;
    }
    printf("接收：%s", _buffer);
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

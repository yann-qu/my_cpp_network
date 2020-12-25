#if !defined(_My_server_H_)
#define _My_server_H_

#include <vector>

class My_server
{
private:
    int listenfd;
    int clientfd;
    //todo: 连接多个client
    // static int clients_connected_num;
    // std::vector<int> clients_fd;

    struct sockaddr_in servaddr;
    struct sockaddr_in clientaddr;

public:
    My_server();

    int create_server_socket(void);
    int config_server(const char *ip_addr, const char *port);
    int acpt_client_connect(void);
    int recv_msg_from_client(char *buffer);
    int send_msg_to_client(char *buffer);
    void close_server_socket(void);

    ~My_server(){};
};

// int My_server::clients_connected_num=0;

#endif // _My_server_H_

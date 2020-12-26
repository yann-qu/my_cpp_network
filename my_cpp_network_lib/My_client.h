#if !defined(_My_client_H_)
#define _My_client_H_

class My_client
{
private:
    int                sockfd;
    struct hostent *   h;
    struct sockaddr_in servaddr;

public:
    My_client(void);

    int  create_client_socket(void);
    int  request_to_connect_server(const char *_h, const char *_port);
    int  send_msg_to_server(const char *_buffer);
    int  recv_msg_from_server(char *_buffer,size_t _buffer_size);
    void close_client_socket(void);

    ~My_client(){};
};

#endif // _My_client_H_

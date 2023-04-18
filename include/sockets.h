#ifndef BENCHMARK_SOCKETS_H
#define BENCHMARK_SOCKETS_H

#define _WIN32_WINNT 0x0601

#include <winsock2.h>
#include <ws2tcpip.h>
#include <string>

#define CONNECT_UDP 0x0A
#define ACCEPT_UDP 0x0B

struct SocketExt {
    SOCKET socket;
    sockaddr_in sock_info;
    int get_ip_str(std::string ip)
    {
        char buffer_ip[32];
        if (inet_ntop(AF_INET, &sock_info.sin_addr, buffer_ip, INET_ADDRSTRLEN) == NULL)
            return 1;
        ip = buffer_ip;
        return 0;
    }
};

int set_client_socket(SocketExt &client_socket, char *server_IP, int port, int t_protocol);
int set_client_socket(SocketExt &client_socket, sockaddr_in server_info, int t_protocol);
int set_server_socket(SocketExt &server_socket, char *server_IP, int port, int t_protocol);
int set_server_socket(SocketExt &server_socket, int t_protocol); // local

int accept_connection(SocketExt &client_socket, SocketExt &server_socket, int t_protocol);
int win_sock_init();

int send_ext(SocketExt &socket, char *buffer, int length, int trans_protocol);
int receive_ext(SocketExt &socket, char *buffer, int length, int trans_protocol);
int get_host_addr(in_addr &host_addr);


#endif

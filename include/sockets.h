#ifndef BENCHMARK_SOCKETS_H
#define BENCHMARK_SOCKETS_H

#define _WIN32_WINNT 0x0601

#include <winsock2.h>
#include <ws2tcpip.h>

#define CONNECT_UDP 0x00

struct SocketExt {
    SOCKET socket;
    sockaddr_in sock_info;
};

int set_client_socket(SocketExt &client_socket, char *server_IP, int port, int t_protocol);
int set_server_socket(SocketExt &server_socket, char *server_IP, int port, int t_protocol);
int accept_connection(SocketExt &client_socket, SocketExt &server_socket, int t_protocol);

int send_ext(SocketExt socket, char *buffer, int length, int trans_protocol);
int receive_ext(SocketExt socket, char *buffer, int length, int trans_protocol);


#endif

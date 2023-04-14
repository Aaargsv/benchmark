#ifndef BENCHMARK_SOCKETS_H
#define BENCHMARK_SOCKETS_H

#define _WIN32_WINNT 0x0601

#include <winsock2.h>

int establish_connection_with_node(SOCKET &socket, char *server_IP, int port, int t_protocol);
int open_server_connection(SOCKET &socket, char *server_IP, int port, int t_protocol);

#endif

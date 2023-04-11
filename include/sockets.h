#ifndef BENCHMARK_SOCKETS_H
#define BENCHMARK_SOCKETS_H

#include <winsock2.h>


int establish_connection_with_node(SOCKET &socket, char *server_IP, int port);
int open_server_connection(SOCKET &socket, char *server_IP, int port);

#endif

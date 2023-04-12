#ifndef TESTS_H
#define TESTS_H

#include <unordered_map>
#include <winsock2.h>

extern std::unordered_map<std::string , SOCKET> map_clients_sockets;

int test_two_nodes(bool is_server, char *server_IP, int port);
int test_four_nodes(bool is_server, char *server_IP, int port);

#endif //TESTS_H

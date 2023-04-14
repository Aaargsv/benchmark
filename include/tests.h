#ifndef TESTS_H
#define TESTS_H

#include <unordered_map>
#include <winsock2.h>

#define PINGING 0x00
#define STOP_PING 0x01
#define INCREMENT_DATA_SIZE 0x02

extern std::unordered_map<std::string , SOCKET> map_clients_sockets;

int test_two_nodes(bool is_server, char *server_IP, int port, int start_data_size, int end_data_size);
int test_four_nodes(bool is_server, char *server_IP, int port);

#endif //TESTS_H

#ifndef TESTS_H
#define TESTS_H

#include <unordered_map>
#include <winsock2.h>

#define PINGING 0x00
#define STOP_PING 0x01
#define INCREMENT_DATA_SIZE 0x02
#define NEXT_STREAM 0x03
#define STOP_STREAM 0x04
#define BYTE_STEP 16

#define IS_SERVER 0x00
#define IS_CLIENT 0x01
#define IS_CONNECTED 0x02

extern std::unordered_map<std::string , SOCKET> map_clients_sockets;

int test_two_nodes(bool is_server, char *server_IP, int port, int start_data_size, int end_data_size, int t_protocol);
int test_four_nodes(bool is_server, char *server_IP, int port);

#endif //TESTS_H

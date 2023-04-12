#include "tests.h"
#include "sockets.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>

struct Mesurement {
    std::chrono::duration<float> avr_duration;
    int data_size;
};

void generate_random_byte_array(char *buf, int len)
{
    srand(time(0));
    for (int i = 0; i < len; i++) {
        buf[i] = static_cast<char>(rand() % 256);
    }
}

int ping(SOCKET server_socket, int start_data_size,
         int power, int repetitions)
{

}

int pong(SOCKET server_socket, int start_data_size,
         int power, int repetitions)
{

}

int test_two_nodes(bool is_server, char *server_IP, int port)
{
    SOCKET server_socket;
    if (is_server) {
        open_server_connection(server_socket, server_IP, port);
        sockaddr_in client_info;
        int client_info_size = sizeof(client_info);
        memset(&client_info, 0, sizeof(client_info));
        SOCKET client_socket = accept(server_socket, (sockaddr*)&client_info, &client_info_size);
        if (client_socket == INVALID_SOCKET) {
            std::cerr << "[Error]: can't accept a client. Error # ";
            std::cerr <<  WSAGetLastError() << std::endl;
            closesocket(server_socket);
            closesocket(client_socket);
            WSACleanup();
            return 1;
        }
        else {
            std::cout << "Connection to a client established successfully" << std::endl;
            char client_IP[32];
            inet_ntop(AF_INET, &client_info.sin_addr, client_IP, INET_ADDRSTRLEN);	// Convert connected client's IP to standard string format
            std::cout << "Client connected with IP address " << client_IP << std::endl;
        }

    } else {
        establish_connection_with_node(server_socket, server_IP, port);
    }
}


int test_four_nodes(bool is_server, char *server_IP, int port)
{

}
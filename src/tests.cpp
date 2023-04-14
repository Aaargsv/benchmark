#include "tests.h"
#include "sockets.h"
#include "stat.h"
#include "plotting.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <random>
#include <ctime>
#include <chrono>
#include <vector>
#include <cmath>


void generate_random_byte_array(char *buf, int len)
{
    srand(time(0));
    for (int i = 0; i < len; i++) {
        buf[i] = static_cast<char>(rand() % 256);
    }
}

int ping(SOCKET server_socket, int start_data_size, int end_data_size,
          std::vector<Mesurement> &mesurements)
{
    std::vector<char> buffer(end_data_size);
 
    int data_size;
    for (data_size = start_data_size; data_size <= end_data_size; data_size++) {
        buffer[0] = PINGING;
        std::vector<double> durations;
        int rep = 1000;
        while (true) {
            generate_random_byte_array(buffer.data() + 1, data_size - 1);
            auto t1 = std::chrono::high_resolution_clock::now();


            int error_code = send(server_socket, buffer.data(), data_size, 0);
            if (error_code == SOCKET_ERROR) {
                std::cout << "[Error]: can't send" << std::endl;
                std::cout << WSAGetLastError() << std::endl;
                return 1;
            }

            error_code = recv(server_socket, buffer.data(), data_size, 0);
            if (error_code == SOCKET_ERROR || error_code == 0) {
                std::cout << "[Error]: can't receive" << std::endl;
                std::cout << WSAGetLastError() << std::endl;
                return 1;
            }

            auto t2 = std::chrono::high_resolution_clock::now();

            durations.push_back(std::chrono::duration<double>(t2 - t1).count() / 2);
            double avr =  average(durations, durations.size());
            double sigma = standard_deviation(durations, durations.size());
            if (sigma <= THRESHOLD * avr)
                break;   
        }

        Mesurement ms;
        ms.avr_duration = average(durations, durations.size());
        ms.data_size = data_size;
        mesurements.push_back(ms);
        buffer[0] = INCREMENT_DATA_SIZE;
        send(server_socket, buffer.data(), data_size, 0);
    }

    buffer[0] = STOP_PING;
    send(server_socket, buffer.data(), data_size, 0);
    return 0;
}

int pong(SOCKET client_socket, int start_data_size, int end_data_size)
{
    std::vector<char> buffer(end_data_size);
    int data_size = start_data_size;
    while (true) {
        int error_code = recv(client_socket, buffer.data(), data_size, 0);
        if (error_code == SOCKET_ERROR || error_code == 0) {
            std::cerr << "[Error]: can't receive" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }
        if (buffer[0] ==  STOP_PING)
            return 0;

        if (buffer[0] == INCREMENT_DATA_SIZE) {
            data_size++;
            continue;
        }
            
        error_code = send(client_socket, buffer.data(), data_size, 0);
        if (error_code == SOCKET_ERROR) {
            std::cout << "[Error]: can't send" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }

    }
}

int test_two_nodes(bool is_server, char *server_IP, int port, int start_data_size, int end_data_size)
{

    if (start_data_size >= end_data_size) {
        std::cout << "[Error]: start_data_size >= end_data_size" << std::endl;
        return 1;
    }

    SOCKET server_socket;
    if (is_server) {
        if(open_server_connection(server_socket, server_IP, port, SOCK_STREAM)) {
            std::cerr << "[Error]: can't open server connection" << std::endl;
            return 1;
        }
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

        if (pong(client_socket, start_data_size, end_data_size)) {
            std::cerr << "[Error]: can't pong" << std::endl;
            return 1;
        } 

    } else {
        if(establish_connection_with_node(server_socket, server_IP, port, SOCK_STREAM)) {
            std::cerr << "[Error]: can't establish connection with node" << std::endl;
            return 1;
        }
        std::vector<Mesurement> mesurements;
        if (ping(server_socket, start_data_size, end_data_size, mesurements)) {
            std::cerr << "[Error]: can't ping" << std::endl;
            return 1;
        }
        
        if (create_plot(mesurements, "ping-pong", "packet size", "delay")) {
            std::cerr << "[Error]: can't plot" << std::endl;
            return 1;
        }
    }
    return 0;
}


int test_four_nodes(bool is_server, char *server_IP, int port)
{

}
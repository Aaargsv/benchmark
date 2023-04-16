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


void generate_random_byte_array(char *buf, int len)
{
    srand(time(0));
    for (int i = 0; i < len; i++) {
        buf[i] = static_cast<char>(rand() % 256);
    }
}

int ping(SOCKET server_socket, int start_data_size, int end_data_size,
          std::vector<Measurement> &measurements)
{
    std::vector<char> buffer(end_data_size);
    int error_code;

    int data_size;
    for (data_size = start_data_size; data_size <= end_data_size; data_size += BYTE_STEP) {
        buffer[0] = PINGING;

        double latency;
        double mean;
        double m2;
        int sample_count = 0;
        double standard_error;
        double sigma;
        double prev_mean = 0;

        generate_random_byte_array(buffer.data() + 1, data_size - 1);
        while (true) {

            auto t1 = std::chrono::steady_clock::now();

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

            auto t2 = std::chrono::steady_clock::now();
            latency = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count() / 2.;
            update_parameters_online(mean, m2, sample_count, latency);

            if (sample_count >= SAMPLE_SIZE && sample_count % CHECK_SAMPLE_SIZE == 0) {
                standard_error = calc_standard_error_online(m2, sample_count);
                sigma = calc_sd_online(m2, sample_count);
                std::cout << "s / m = " << standard_error /  mean << std::endl;
                if (sigma * THRESHOLD > abs(prev_mean - mean))
                    break;
                prev_mean = mean;
            }

        }

        Measurement ms;
        ms.value = mean / 1e6;
        ms.data_size = data_size;
        measurements.push_back(ms);
        if (data_size + BYTE_STEP < end_data_size) {
            buffer[0] = INCREMENT_DATA_SIZE;
            send(server_socket, buffer.data(), data_size, 0);
        }
    }

    buffer[0] = STOP_PING;
    send(server_socket, buffer.data(), data_size, 0);
    return 0;
}

int pong(SOCKET client_socket, int start_data_size, int end_data_size)
{
    std::vector<char> buffer(end_data_size);
    int error_code;
    int data_size = start_data_size;
    while (true) {
        error_code = recv(client_socket, buffer.data(), data_size, 0);
        if (error_code == SOCKET_ERROR || error_code == 0) {
            std::cerr << "[Error]: can't receive" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }

        if (buffer[0] == STOP_PING)
            return 0;

        if (buffer[0] == INCREMENT_DATA_SIZE) {
            data_size += BYTE_STEP;
            std::cout << data_size << std::endl;
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

int stream_receive(SOCKET server_socket, int start_data_size, int end_data_size, std::vector<Measurement> &measurements)
{
    std::vector<char> buffer(end_data_size);
    int error_code;
    int data_size;
    for (data_size = start_data_size; data_size <= end_data_size; data_size += BYTE_STEP) {
        double time;
        double bandwidth;
        double mean;
        double m2;
        int sample_count = 0;
        double sigma;
        double prev_mean;

        while (true) {
            auto t1 = std::chrono::steady_clock::now();
            error_code = recv(server_socket, buffer.data(), data_size, 0);
            if (error_code == SOCKET_ERROR || error_code == 0) {
                std::cout << "[Error]: can't receive" << std::endl;
                std::cout << WSAGetLastError() << std::endl;
                return 1;
            }

            auto t2 = std::chrono::steady_clock::now();
            time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            bandwidth = data_size / time;
            update_parameters_online(mean, m2, sample_count, bandwidth);
            sigma = calc_sd_online(m2, sample_count);

            if (sample_count >= SAMPLE_SIZE && sigma * THRESHOLD < abs(bandwidth - mean))
                break;

            if (sample_count >= SAMPLE_SIZE && sample_count % CHECK_SAMPLE_SIZE == 0) {
                sigma = calc_sd_online(m2, sample_count);
                if (sigma * THRESHOLD < abs(prev_mean - mean))
                    break;
                prev_mean = mean;
            }
            buffer[0] = NEXT_STREAM;
            send(server_socket, buffer.data(), 1, 0);
        }

        Measurement ms;
        ms.value = mean * 1e9 / 125000;
        ms.data_size = data_size;
        measurements.push_back(ms);
        if (data_size + BYTE_STEP < end_data_size) {
            buffer[0] = INCREMENT_DATA_SIZE;
            send(server_socket, buffer.data(), 1, 0);
        }
    }

    buffer[0] = STOP_STREAM;
    send(server_socket, buffer.data(), 1, 0);
    return 0;
}


int stream_send(SOCKET client_socket, int start_data_size, int end_data_size)
{
    std::vector<char> buffer(end_data_size);
    int error_code;
    int data_size = start_data_size;
    char command;
    generate_random_byte_array(buffer.data(), data_size);
    while (true) {

        error_code = send(client_socket, buffer.data(), data_size, 0);
        if (error_code == SOCKET_ERROR) {
            std::cout << "[Error]: can't send" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }

        error_code = recv(client_socket, &command, 1, 0);
        if (error_code == SOCKET_ERROR || error_code == 0) {
            std::cout << "[Error]: can't receive. Error number: ";
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }

        if (command == NEXT_STREAM)
            continue;

        if (command == INCREMENT_DATA_SIZE) {
            data_size += BYTE_STEP;
            generate_random_byte_array(buffer.data(), data_size);
            std::cout << data_size << std::endl;
            continue;
        }

        if (command == STOP_STREAM)
            return 0;
    }
}


int test_two_nodes(bool is_server, char *server_IP, int port, int start_data_size, int end_data_size, int t_protocol)
{

    if (start_data_size >= end_data_size) {
        std::cout << "[Error]: start_data_size >= end_data_size" << std::endl;
        return 1;
    }

    SOCKET server_socket;
    if (is_server) {
        if(open_server_connection(server_socket, server_IP, port, t_protocol)) {
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

        if (stream_send(client_socket, start_data_size, end_data_size)) {
            std::cout << "[Error]: can't send stream" << std::endl;
            return 1;
        }

    } else {
        if(establish_connection_with_node(server_socket, server_IP, port, t_protocol)) {
            std::cerr << "[Error]: can't establish connection with node" << std::endl;
            return 1;
        }
        std::vector<Measurement> measurements_ping_pong;

        auto t1 = std::chrono::steady_clock::now();
        if (ping(server_socket, start_data_size, end_data_size, measurements_ping_pong)) {
            std::cerr << "[Error]: can't ping" << std::endl;
            return 1;
        }
        auto t2 = std::chrono::steady_clock::now();

        std::cout << "Ping time: " << std::chrono::duration_cast<std::chrono::seconds>(t2 - t1).count() << std::endl;

        print_measurements(measurements_ping_pong);

        std::vector<Measurement> measurements_stream;
        if (stream_receive(server_socket, start_data_size, end_data_size, measurements_stream)) {
            std::cerr << "[Error]: can't receive stream" << std::endl;
            return 1;
        }
        
        if (create_plot(measurements_ping_pong, "ping-pong", "packet size (byte)", "delay (ms)")) {
            std::cerr << "[Error]: can't plot" << std::endl;
            return 1;
        }

        if (create_plot(measurements_stream, "stream", "packet size (byte)", "bandwidth (Mbps)")) {
           std::cerr << "[Error]: can't plot" << std::endl;
           return 1;
        }
    }
    return 0;
}


int test_four_nodes(bool is_server, char *server_IP, int port)
{
    return 0;
}
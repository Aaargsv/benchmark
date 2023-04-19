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
#include <thread>
#include <vector>
#include <assert.h>



void generate_random_byte_array(char *buf, int len)
{
    srand(time(0));
    for (int i = 0; i < len; i++) {
        buf[i] = static_cast<char>(rand() % 256);
    }
}

int ping(SocketExt server_socket, int start_data_size, int end_data_size, int trans_protocol,
          std::vector<Measurement> &measurements)
{
    std::vector<char> buffer(end_data_size);
    int error_code;

    int data_size;
    for (data_size = start_data_size; data_size <= end_data_size; data_size += BYTE_STEP) {
        buffer[0] = PINGING;

        double latency;
        double mean = 0;
        double m2;
        int sample_count = 0;
        double standard_error;
        double sigma;
        double prev_mean = 0;

        generate_random_byte_array(buffer.data() + 1, data_size - 1);
        while (true) {
            assert(data_size <= end_data_size);
            auto t1 = std::chrono::steady_clock::now();

            if (send_ext(server_socket, buffer.data(), data_size, trans_protocol))
                return 1;
            if (receive_ext(server_socket, buffer.data(), data_size, trans_protocol))
                return 1;

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
            if (send_ext(server_socket, buffer.data(), 1, trans_protocol))
                return 1;
        }
    }

    buffer[0] = STOP_PING;
    if (send_ext(server_socket, buffer.data(), 1, trans_protocol))
        return 1;
    return 0;
}

int pong(SocketExt client_socket, int start_data_size, int end_data_size, int trans_protocol)
{
    std::vector<char> buffer(end_data_size);
    int error_code;
    int data_size = start_data_size;
    while (true) {
        assert(data_size <= end_data_size);
        if (receive_ext(client_socket, buffer.data(), data_size, trans_protocol))
            return 1;

        if (buffer[0] == STOP_PING)
            return 0;

        if (buffer[0] == INCREMENT_DATA_SIZE) {
            data_size += BYTE_STEP;
            std::cout << data_size << std::endl;
            continue;
        }

        if (send_ext(client_socket, buffer.data(), data_size, trans_protocol))
            return 1;
    }
}

int stream_receive(SocketExt server_socket, int start_data_size, int end_data_size, int trans_protocol,
                   std::vector<Measurement> &measurements)
{
    std::vector<char> buffer(end_data_size);
    int error_code;
    int data_size;
    for (data_size = start_data_size; data_size <= end_data_size; data_size += BYTE_STEP) {
        double time;
        double bandwidth;
        double mean = 0;
        double m2;
        int sample_count = 0;
        double sigma;
        double prev_mean = 0;

        while (true) {
            assert(data_size <= end_data_size);
            auto t1 = std::chrono::steady_clock::now();
            if (receive_ext(server_socket, buffer.data(), data_size, trans_protocol))
                return 1;

            auto t2 = std::chrono::steady_clock::now();
            time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
            bandwidth = data_size / time;
            update_parameters_online(mean, m2, sample_count, bandwidth);

            if (sample_count >= SAMPLE_SIZE && sample_count % CHECK_SAMPLE_SIZE == 0) {
                sigma = calc_sd_online(m2, sample_count);
                if (sigma * THRESHOLD < abs(prev_mean - mean))
                    break;
                prev_mean = mean;
            }
            buffer[0] = NEXT_STREAM;
            if (send_ext(server_socket, buffer.data(), 1, trans_protocol))
                return 1;
        }

        Measurement ms;
        ms.value = mean * 1e9 / 125000;
        ms.data_size = data_size;
        measurements.push_back(ms);
        if (data_size + BYTE_STEP <= end_data_size) {
            buffer[0] = INCREMENT_DATA_SIZE;
            if (send_ext(server_socket, buffer.data(), 1, trans_protocol))
                return 1;
        }
    }

    buffer[0] = STOP_STREAM;
    if (send_ext(server_socket, buffer.data(), 1, trans_protocol))
        return 1;
    return 0;
}


int stream_send(SocketExt client_socket, int start_data_size, int end_data_size, int trans_protocol)
{
    std::vector<char> buffer(end_data_size);
    int error_code;
    int data_size = start_data_size;
    char command;
    generate_random_byte_array(buffer.data(), data_size);
    while (data_size <= end_data_size) {

        assert(data_size <= end_data_size);

        if (send_ext(client_socket, buffer.data(), data_size, trans_protocol))
            return 1;

        if (receive_ext(client_socket, &command, 1, trans_protocol))
            return 1;

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
    return 0;
}

int get_socket_index(std::vector<SocketExt> &vs, SOCKET sock)
{
    for (int i = 0; i < vs.size(); i++) {
        if (vs[i].socket == sock)
            return i;
    }
    return -1;
}

int multiple_stream_receive(std::vector<SocketExt> &vec_sockets, fd_set recv_set, int max_socket_num, int start_data_size, int end_data_size,
                            int trans_protocol, int num_nodes, std::vector<std::vector<Measurement>> &node_mes)
{

    std::vector<char> buffer(end_data_size);
    int error_code;
    std::vector<int> data_size(num_nodes, start_data_size);
    fd_set temp_recv_set;
    memcpy(&temp_recv_set, &recv_set, sizeof (fd_set));

    struct StatValues {
        double time = 0;
        double bandwidth = 0;
        double mean = 0;
        double m2 = 0;
        int sample_count = 0;
        double sigma = 0;
        double prev_mean = 0;
        int is_next_size = 0;
    };

    std::vector<StatValues> vec_stat(num_nodes);
    while (true) {
        for (int i = 0; i < num_nodes; i++) {
            if (vec_stat[i].is_next_size) {
                data_size[i] += BYTE_STEP;
                vec_stat[i].is_next_size = 0;
                memset(&vec_stat[i], 0, sizeof (StatValues));
            }
        }

        bool is_finished = true;
        for (int i = 0; i < num_nodes; i++) {
            if (data_size[i] <= end_data_size) {
                is_finished = false;
            }
        }
        if (is_finished)
            break;
        error_code = select(max_socket_num, &recv_set, NULL, NULL, NULL); /****/
        if (error_code < 0) {
            std::cerr << "[Error]: can't select" << std::endl;
            return 1;
        }
        for (int i = 0; i < num_nodes; i++) {
            if (FD_ISSET(vec_sockets[i].socket, &recv_set)) {
                int index = i;
                if (data_size[index] > end_data_size)
                    continue;

                auto t1 = std::chrono::steady_clock::now();
                if (receive_ext(vec_sockets[index], buffer.data(), data_size[index], trans_protocol))
                    return 1;
                auto t2 = std::chrono::steady_clock::now();
                vec_stat[index].time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
                vec_stat[index].bandwidth = data_size[index] / vec_stat[index].time;
                update_parameters_online(vec_stat[index].mean, vec_stat[index].m2, vec_stat[index].sample_count, vec_stat[index].bandwidth);
                if (vec_stat[index].sample_count >= SAMPLE_SIZE && vec_stat[index].sample_count % CHECK_SAMPLE_SIZE == 0) {

                    double standard_error = calc_standard_error_online(vec_stat[index].m2, vec_stat[index].sample_count);
                    std::cout << "s / m = " << standard_error /  vec_stat[index].mean << std::endl;


                    vec_stat[index].sigma = calc_sd_online(vec_stat[index].m2, vec_stat[index].sample_count);
                    if (vec_stat[index].sigma * THRESHOLD < abs(vec_stat[index].prev_mean - vec_stat[index].mean)) {
                        Measurement ms;
                        ms.value = vec_stat[index].mean * 1e9 / 125000;
                        ms.data_size = data_size[index];
                        node_mes[index].push_back(ms);
                        vec_stat[index].is_next_size = 1;
                        buffer[0] = INCREMENT_DATA_SIZE;
                        if (send_ext(vec_sockets[index], buffer.data(), 1, trans_protocol))
                            return 1;
                        continue;
                    }

                    vec_stat[index].prev_mean = vec_stat[index].mean;
                }
                buffer[0] = NEXT_STREAM;
                if (send_ext(vec_sockets[index], buffer.data(), 1, trans_protocol))
                    return 1;
            }
        }
        memcpy(&recv_set, &temp_recv_set, sizeof (fd_set));
    }

    return 0;
}

int multiple_stream_send(std::vector<SocketExt> &vec_socket, int num_nodes, int start_data_size,
                         int end_data_size, int trans_protocol)
{
    std::vector<char> buffer(end_data_size);
    generate_random_byte_array(buffer.data(), end_data_size);
    std::vector<int> data_size(num_nodes, start_data_size);
    char command;

    while (true) {
        bool is_finished = true;
        for (int i = 0; i < num_nodes;  i++) {
            if (data_size[i] <= end_data_size) {
                is_finished = false;
                break;
            }
        }
        if (is_finished)
            break;

        int index = rand() % num_nodes;

        if (data_size[index] > end_data_size)
            continue;
        SocketExt rand_sock = vec_socket[index];
        if (send_ext(rand_sock, buffer.data(), data_size[index], trans_protocol))
            return 1;
        if (receive_ext(rand_sock, &command, 1 , trans_protocol))
            return 1;
        if (command == NEXT_STREAM)
            continue;
        if (command == INCREMENT_DATA_SIZE) {
            data_size[index] += BYTE_STEP;
            //std::cout << "send stream: " << data_size[index] << std::endl;
        }
    }
    return 0;
}

int test_two_nodes(bool is_server, char *server_IP, int port, int start_data_size, int end_data_size, int t_protocol)
{

    if (start_data_size >= end_data_size) {
        std::cout << "[Error]: start_data_size >= end_data_size" << std::endl;
        return 1;
    }
    std::string prot = (t_protocol == SOCK_STREAM) ? "tcp": "udp";
    SocketExt server_socket;
    if (is_server) {

        if(set_server_socket(server_socket, server_IP, port, t_protocol)) {
            std::cerr << "[Error]: can't open server connection" << std::endl;
            return 1;
        }
        SocketExt client_socket;

        if (accept_connection(client_socket, server_socket, t_protocol)) {
            std::cerr << "[Error]: can't accept connection" << std::endl;
            return 1;
        }


        if (pong(client_socket, start_data_size, end_data_size, t_protocol)) {
            std::cerr << "[Error]: can't pong" << std::endl;
            return 1;
        }

        if (stream_send(client_socket, start_data_size, end_data_size, t_protocol)) {
            std::cout << "[Error]: can't send stream" << std::endl;
            return 1;
        }

    } else {
        if(set_client_socket(server_socket, server_IP, port, t_protocol)) {
            std::cerr << "[Error]: can't set client socket" << std::endl;
            return 1;
        }
        std::vector<Measurement> measurements_ping_pong;

        if (ping(server_socket, start_data_size, end_data_size, t_protocol, measurements_ping_pong)) {
            std::cerr << "[Error]: can't ping" << std::endl;
            return 1;
        }

        print_measurements(measurements_ping_pong);

        std::vector<Measurement> measurements_stream;
        if (stream_receive(server_socket, start_data_size, end_data_size, t_protocol, measurements_stream)) {
            std::cerr << "[Error]: can't receive stream" << std::endl;
            return 1;
        }
        
        if (create_plot(measurements_ping_pong, "ping-pong-" + prot, "packet size (byte)", "delay (ms)")) {
            std::cerr << "[Error]: can't plot" << std::endl;
            return 1;
        }

        if (create_plot(measurements_stream, "stream-" + prot, "packet size (byte)", "bandwidth (Mbps)")) {
           std::cerr << "[Error]: can't plot" << std::endl;
           return 1;
        }
    }
    return 0;
}


int test_multiple_nodes_stream(int num_nodes, bool is_server, char *server_IP, int port,
                               int start_data_size, int end_data_size, int t_protocol)
{
    static std::vector<SocketExt> vec_sockets;
    if (is_server) {
        SocketExt server_socket;
        if (set_server_socket(server_socket, server_IP, port, SOCK_STREAM)) {
            std::cerr << "[Error]: can't open server connection" << std::endl;
            return 1;
        }

        for (int i = 0; i < num_nodes - 1; i++) {
            SocketExt node_sock;
            if (accept_connection(node_sock, server_socket, SOCK_STREAM)) {
                std::cerr << "[Error]: can't accept connection" << std::endl;
                return 1;
            }
            vec_sockets.push_back(node_sock);
        }

        int data_size = sizeof (sockaddr_in);
        std::vector<char> buffer(data_size);
        char command;
        for (int i = 0; i < num_nodes - 1; i++) {
            for (int j = i + 1; j < num_nodes - 1; j++) {

                command = IS_SERVER;
                if (send_ext(vec_sockets[i], &command, 1, SOCK_STREAM))
                    return 1;
                if (receive_ext(vec_sockets[i], buffer.data(), data_size, SOCK_STREAM))
                    return 1;
                command = IS_CLIENT;
                if (send_ext(vec_sockets[j], &command, 1, SOCK_STREAM))
                    return 1;
                if (send_ext(vec_sockets[j], buffer.data(), data_size, SOCK_STREAM))
                    return 1;
            }
        }
    } else {
        SocketExt server_socket;
        set_client_socket(server_socket, server_IP, port, SOCK_STREAM);

        int data_size = sizeof (char) + sizeof (sockaddr_in);
        std::vector<char> buffer(data_size);
        for (int i = 0; i < num_nodes - 2; i++) {
            SocketExt node_sock;
            if (receive_ext(server_socket, buffer.data(), 1, SOCK_STREAM))
                return 1;
            if (buffer[0] == IS_SERVER) {
                SocketExt opposite_node_sock;
                if(set_server_socket(node_sock, SOCK_STREAM))
                    return 1;
                if(send_ext(server_socket, (char*)&node_sock.sock_info, sizeof (node_sock.sock_info), SOCK_STREAM))
                    return 1;
                if (accept_connection(opposite_node_sock, node_sock, SOCK_STREAM))
                    return 1;
                vec_sockets.push_back(opposite_node_sock);
            }
            if (buffer[0] == IS_CLIENT) {
                sockaddr_in opposite_node_info;
                if (receive_ext(server_socket, (char*)&opposite_node_info,  sizeof (sockaddr_in), SOCK_STREAM))
                    return 1;

                SocketExt s;
                s.sock_info = opposite_node_info;
                std::string str;
                s.get_ip_str(str);
                std::cout << str << std::endl;

                if (set_client_socket(node_sock, opposite_node_info, SOCK_STREAM))
                    return 1;
                vec_sockets.push_back(node_sock);
            }
        }
        vec_sockets.push_back(server_socket);
    }

    fd_set recv_set;
    FD_ZERO(&recv_set);
    for (int i = 0; i < num_nodes - 1; i++) {
        FD_SET(vec_sockets[i].socket, &recv_set);
    }
    int max_socket_num = 0;
    for (int i = 0; i < num_nodes - 1; i++) {
        if (vec_sockets[i].socket > max_socket_num)
            max_socket_num = vec_sockets[i].socket;
    }
    max_socket_num++;
    std::vector<std::vector<Measurement>> node_ms(num_nodes - 1);
    std::thread th_receive(multiple_stream_receive, std::ref(vec_sockets), recv_set,
                           max_socket_num, start_data_size, end_data_size,
                           t_protocol, num_nodes - 1, std::ref(node_ms));

    std::thread th_send(multiple_stream_send, std::ref(vec_sockets), num_nodes - 1,
                        start_data_size, end_data_size, t_protocol);

    th_receive.join();
    th_send.join();

    std::string ip;
    std::string plot_name;

    for (int i = 0; i < num_nodes - 1; i++) {
        if (vec_sockets[i].get_ip_str(ip)) {
            std::cout << "[Error]: can't get ip str" << std::endl;
            return 1;
        };
        plot_name = "stream - " + ip;
        if (create_plot(node_ms[i], plot_name, "packet size (byte)", "delay (ms)")) {
            std::cerr << "[Error]: can't plot" << std::endl;
            return 1;
        }
    }
    return 0;
}
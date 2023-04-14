#include "tests.h"
#include <winsock2.h>
#include <thread>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>

int main(int argc, char *argv[])
{
    char server_IP[16];
    int port;
    int num_nodes;
    bool is_server = false;
    bool are_settings_in_file = false;
    std::string settings_file_name;

    /**
     * [program] [2]
     * [program] [2] [-s/-c] [settings file name]
     * [program] [2] [-s/-c] [ip] [port]
     * [program] [4] [-s/-c]
     * [program] [4] [-s/-c] [settings file name]
     * [program] [4] [-s/-c] [ip] [port]
     */

    if (argc < 3) {
        std::cerr << "[Error]: too few arguments" << std::endl;
        return 1;
    } else {
        if (strcmp(argv[2], "-s") == 0) {
            is_server = true;
        } else if (strcmp(argv[2], "-c") == 0) {
            is_server = false;
        } else {
            std::cerr << "[Error]: unknown argument" << std::endl;
            return 1;
        }

        if (strcmp(argv[1], "2") == 0) {
            num_nodes = 2;
        } else if (strcmp(argv[1], "4") == 0) {
            num_nodes = 4;
        } else {
            std::cerr << "[Error]: wrong numbers of nodes" << std::endl;
            return 1;
        }

        if (argc == 3) {
            are_settings_in_file = true;
            settings_file_name = "settings.txt";
        } else if (argc == 4) {
            are_settings_in_file = true;
            settings_file_name = argv[3];
        } else if (argc >= 5) {
            strncpy(server_IP, argv[3], 16);
            port = std::stoi(std::string(argv[4]));
        }
    }

    /// read ip and port from settings file
    if (are_settings_in_file) {
        std::ifstream settings_file(settings_file_name);
        if (!settings_file) {
            std::cerr << "[Error]: can't open settings file" << std::endl;
            return 1;
        }
        std::string buffer_ip;
        std::string buffer_port;
        if (!(settings_file >> buffer_ip >> buffer_port)) {
            std::cerr << "[Error]: wrong settings format" << std::endl;
            return 1;
        }
        strncpy(server_IP, buffer_ip.c_str(), 16);
        port = std::stoi(buffer_port);
    }

    if (num_nodes == 2)
        test_two_nodes(is_server, server_IP, port, 1, 1024);
    

    return 0;
}
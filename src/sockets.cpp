#define _WIN32_WINNT 0x0601
#include "sockets.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

int establish_connection_with_node(SOCKET &client_socket, char *server_IP, int port, int t_protocol)
{
    int error_code;
    in_addr ip_to_num;

    error_code = inet_pton(AF_INET, server_IP, &ip_to_num);
    if (error_code <= 0) {
        std::cerr << "[Error]: can't translate IP address to special numeric format" << std::endl;
        return 1;
    }

    // WinSock initialization
    WSADATA wsData;
    error_code = WSAStartup(MAKEWORD(2,2), &wsData);
    if ( error_code != 0 ) {
        std::cerr << "[Error]: WinSock version initialization # ";
        std::cerr << WSAGetLastError() << std:: endl;
        return 1;
    }
    else
        std::cout << "WinSock initialization is OK" << std::endl;

    client_socket = socket(AF_INET, t_protocol, 0);
    if (client_socket == INVALID_SOCKET) {
        std::cerr << "[Error]: can't initialize socket # ";
        std::cerr << WSAGetLastError() << std:: endl;
        closesocket(client_socket);
        WSACleanup();
    }
    else
        std::cout << "Client socket initialization is OK" << std::endl;

    sockaddr_in server_info;
    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_addr = ip_to_num;
    server_info.sin_port = htons(port);

    error_code = connect(client_socket, (sockaddr*)&server_info, sizeof(server_info));

    if (error_code != 0) {
        std::cerr << "[Error]: can't connect to node # " ;
        std::cerr << WSAGetLastError() << std::endl;
        closesocket(client_socket);
        WSACleanup();
        return 1;
    }
    else
        std::cout << "Connection established successfully" << std::endl;
    return 0;
}

int open_server_connection(SOCKET &server_socket, char *server_IP, int port, int t_protocol)
{
    int error_code;
    in_addr ip_to_num;

    error_code = inet_pton(AF_INET, server_IP, &ip_to_num);
    if (error_code <= 0) {
        std::cerr << "[Error]: can't translate IP address to special numeric format" << std::endl;
        return 1;
    }

    // WinSock initialization
    WSADATA wsData;
    error_code = WSAStartup(MAKEWORD(2,2), &wsData);
    if ( error_code != 0 ) {
        std::cerr << "[Error]: WinSock version initialization # ";
        std::cerr << WSAGetLastError() << std:: endl;
        return 1;
    }
    else
        std::cout << "WinSock initialization is OK" << std::endl;

    // Server socket initialization
    server_socket = socket(AF_INET, t_protocol, 0);
    if (server_socket == INVALID_SOCKET) {
        std::cerr << "[Error]: can't initialize socket # ";
        std::cerr << WSAGetLastError() << std:: endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    else
        std::cout << "Server socket initialization is OK" << std::endl;

    // Server socket binding
    sockaddr_in server_info;
    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_addr = ip_to_num;
    server_info.sin_port = htons(port);

    error_code = bind(server_socket, (sockaddr*)&server_info, sizeof(server_info));
    if ( error_code != 0 ) {
        std::cerr << "[Error]: can't bind socket to server info. Error # ";
        std::cerr <<  WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    else
        std::cout << "Binding socket to Server info is OK" << std::endl;

    //Starting to listen to any Clients
    error_code = listen(server_socket, SOMAXCONN);
    if ( error_code != 0 ) {
        std::cerr << "[Error]: can't start to listen to. Error # ";
        std::cerr <<  WSAGetLastError() << std::endl;
        closesocket(server_socket);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Listening..." << std::endl;
    }
    return 0;
}
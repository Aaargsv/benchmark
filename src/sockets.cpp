#define _WIN32_WINNT 0x0601
#include "sockets.h"
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

int set_client_socket(SocketExt &client_socket, char *server_IP, int port, int t_protocol)
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

    client_socket.socket = socket(AF_INET, t_protocol, 0);
    if (client_socket.socket == INVALID_SOCKET) {
        std::cerr << "[Error]: can't initialize socket # ";
        std::cerr << WSAGetLastError() << std:: endl;
        closesocket(client_socket.socket);
        WSACleanup();
    }
    else
        std::cout << "Client socket initialization is OK" << std::endl;

    sockaddr_in server_info;
    memset(&server_info, 0, sizeof(server_info));
    server_info.sin_family = AF_INET;
    server_info.sin_addr = ip_to_num;
    server_info.sin_port = htons(port);
    client_socket.sock_info = server_info;

    if (t_protocol == SOCK_STREAM) {
        error_code = connect(client_socket.socket, (sockaddr*)&server_info, sizeof(server_info));
        if (error_code != 0) {
            std::cerr << "[Error]: can't connect to node # " ;
            std::cerr << WSAGetLastError() << std::endl;
            closesocket(client_socket.socket);
            WSACleanup();
            return 1;
        } else
            std::cout << "Connection established successfully" << std::endl;
    } else {
        sockaddr_in client_info = {};
        server_info.sin_family = AF_INET;
        error_code = bind(client_socket.socket, reinterpret_cast<const sockaddr *>(&client_info), sizeof(client_info));
        if ( error_code != 0 ) {
            std::cerr << "[Error]: can't bind udp socket. Error: ";
            std::cerr <<  WSAGetLastError() << std::endl;
            closesocket(client_socket.socket);
            WSACleanup();
            return 1;
        }
        char data = CONNECT_UDP;
        if (send_ext(client_socket, &data, 1, t_protocol))
            return 1;
    }
    return 0;
}



int set_server_socket(SocketExt &server_socket, char *server_IP, int port, int t_protocol)
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
    server_socket.socket = socket(AF_INET, t_protocol, 0);
    if (server_socket.socket == INVALID_SOCKET) {
        std::cerr << "[Error]: can't initialize socket # ";
        std::cerr << WSAGetLastError() << std:: endl;
        closesocket(server_socket.socket);
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

    error_code = bind(server_socket.socket, (sockaddr*)&server_info, sizeof(server_info));
    if ( error_code != 0 ) {
        std::cerr << "[Error]: can't bind socket to server info. Error # ";
        std::cerr <<  WSAGetLastError() << std::endl;
        closesocket(server_socket.socket);
        WSACleanup();
        return 1;
    }
    else
        std::cout << "Binding socket to Server info is OK" << std::endl;


    if (t_protocol == SOCK_DGRAM)
        return 0;

    //Starting to listen to any Clients
    error_code = listen(server_socket.socket, SOMAXCONN);
    if ( error_code != 0 ) {
        std::cerr << "[Error]: can't start to listen to. Error # ";
        std::cerr <<  WSAGetLastError() << std::endl;
        closesocket(server_socket.socket);
        WSACleanup();
        return 1;
    }
    else {
        std::cout << "Listening..." << std::endl;
    }
    return 0;
}

int accept_connection(SocketExt &client_socket, SocketExt &server_socket, int t_protocol)
{
    sockaddr_in client_info;
    int client_info_size = sizeof(client_info);
    memset(&client_info, 0, sizeof(client_info));

    if (t_protocol == SOCK_STREAM) {
        client_socket.socket = accept(server_socket.socket, (sockaddr*)&client_info, &client_info_size);
        if (client_socket.socket == INVALID_SOCKET) {
            std::cerr << "[Error]: can't accept a client. Error # ";
            std::cerr <<  WSAGetLastError() << std::endl;
            closesocket(server_socket.socket);
            closesocket(client_socket.socket);
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
        char data;
        if (receive_ext(server_socket, &data, 1, t_protocol))
            return 1;
    }

    return 0;
}

int send_ext(SocketExt sock, char *buffer, int length, int trans_protocol)
{
    int error_code;
    if (trans_protocol == SOCK_STREAM) {
        error_code= send(sock.socket, buffer, length, 0);
        if (error_code == SOCKET_ERROR) {
            std::cout << "[Error]: can't send" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }
    } else if (trans_protocol == SOCK_DGRAM) {
        error_code = sendto(sock.socket, buffer, length, 0, reinterpret_cast<const sockaddr *>(&sock.sock_info), sizeof(sock.sock_info));
        if (error_code == SOCKET_ERROR) {
            std::cout << "[Error]: can't send" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }
    } else
        return 1;
    return 0;
}
int receive_ext(SocketExt sock, char *buffer, int length, int trans_protocol)
{
    int error_code;
    int addr_size = sizeof(sock.sock_info);
    if (trans_protocol == SOCK_STREAM) {
        error_code= recv(sock.socket, buffer, length, 0);
        if (error_code == SOCKET_ERROR) {
            std::cout << "[Error]: can't send" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }
    } else if (trans_protocol == SOCK_DGRAM) {
        error_code = recvfrom(sock.socket, buffer, length, 0, reinterpret_cast<sockaddr *> (&sock.sock_info), &addr_size);
        if (error_code == SOCKET_ERROR) {
            std::cout << "[Error]: can't send" << std::endl;
            std::cout << WSAGetLastError() << std::endl;
            return 1;
        }
    } else
        return 1;
    return 0;
}


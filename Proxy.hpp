#ifndef PROXY_HPP
#define PROXY_HPP

#define BACKLOG_SIZE 1
#define BUFFER_SIZE 262144

#include <cstdint>
#include <cstring>
#include <iostream>
#include <thread>
#include <vector>
#include <memory>

#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>

#include "HttpRequest.hpp"
#include "TcpConnection.hpp"
#include "ImageSubstitution.hpp"



class Proxy {

private:
    uint16_t port_number;
    char buffer[BUFFER_SIZE];
    int attack_mode;
    int substitution_mode;
public:
    Proxy(uint16_t port_number, int attack_mode, int substitution_mode) {
        this->port_number = port_number;
        this->attack_mode = attack_mode;
        this->substitution_mode = substitution_mode;
    }

    void StartProxy();
    void HandleConnection(int client_socket_fd);
    int CreateTCPConnectionToServer(uint16_t server_port_number, const char * server_ip);
    void HandleClientToServer(int client_socket_fd,int server_socket_fd);
    void HandleServerToClient(int client_socket_fd,int server_socket_fd);
    void HandleServerToClientImageSubstitution(int client_socket_fd,int server_socket_fd);
    void HandleAttackMode(int client_socket_fd);

};

#endif
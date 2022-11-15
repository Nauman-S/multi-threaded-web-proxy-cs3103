#include "TcpConnection.hpp"

int TcpConnection::Create(uint16_t server_port_number,const char * server_ip) {
     //Initialize the socket
    int server_socket_fd;
    if ((server_socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 1 ) {
        std::cout << "Unable to Create TCP socket" << std::endl;
        return -1;
    }

    struct sockaddr_in server_socket_address;
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_port = htons(server_port_number);
    memset(&(server_socket_address.sin_zero), 0, 8);

    if (inet_pton(AF_INET, server_ip, &server_socket_address.sin_addr) <= 0) {
        std::cout << "Unable to Interpret Server Ip" << std::endl;
        return -1;
    }

    // Create TCP Connection to Server
    if (connect(server_socket_fd,(struct sockaddr*)&server_socket_address,sizeof(server_socket_address)) == -1) {
        std::cout << "TCP Connection to Server Failed " << std::endl;
        return -1;
    }
    return server_socket_fd;
}
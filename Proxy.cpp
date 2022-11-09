#include  "Proxy.hpp"

#include <cstring>
#include <iostream>
#include <thread>

#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>


void Proxy::StartProxy() {
     //Initialize the socket
    int socket_fd;
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 1 ) {
        std::cout << "Unable to create TCP socket " << std::endl;
        exit(EXIT_FAILURE);
    }

    // Initialize sockaddr struct - here socket is given IP, protocol and port
    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET; // Ensure server is binding to local IP address
    socket_address.sin_port = htons(port_number);
    //memset(&(socket_address.sin_zero), 0, 8);


    //Bind socket (socket_fd) to port, protocl and IP (socket_address)
    if (bind(socket_fd, (struct sockaddr*)&socket_address,sizeof(socket_address))< 0) {
        std::cout <<"Unable to bind socket to port" << std::endl;
        exit(EXIT_FAILURE);
    }

    //Bind socket to listen to local port
    if (listen(socket_fd, BACKLOG_SIZE) == -1) {
        std::cout << "Unable to listen to connections on port " << std::endl;
        exit(EXIT_FAILURE);
    }

    //Accept client connections on handle them on different sockets using multithreading
    int new_socket_fd;
    for (;;) {
        if ((new_socket_fd = accept(socket_fd, NULL, NULL)) < 0) {
            std::cout << "Unable to accept client connection" << std::endl;
            exit(EXIT_FAILURE);
        }
        std::thread thread{&Proxy::HandleConnection,this,new_socket_fd};
        thread.detach();
    }
}

void Proxy::HandleConnection(int client_socket_fd) {
    memset(buffer,0,1024);
    ssize_t bytes_read;
    while ((bytes_read = read(client_socket_fd, buffer, 1024)) > 0) {
        printf("%s",buffer);
    }
    return;
}

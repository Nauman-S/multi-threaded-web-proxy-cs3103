#include  "Proxy.hpp"

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
    memset(&(socket_address.sin_zero), 0, 8);


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
    //Read from client
    memset(buffer,0,1024);
    ssize_t bytes_read;
    HttpRequest http_request;
    if ((bytes_read = read(client_socket_fd, buffer, 1024)) > 0) {
        printf("%s",buffer);
    } else {
        close(client_socket_fd);
        return;
    }

    std::shared_ptr<HttpRequestDetails> request = http_request.parse(bytes_read, buffer);
    if (request->is_valid) {
        std::cout << "Valid Request" << std::endl;
        std::cout << request->ip_address << std::endl;
        std::cout << request->port_number << std::endl;
    } else {
        std::cout << "Invalid Request" << std::endl;
        close(client_socket_fd);
        return;
    }

    //Write to server
    //CreateTCPConnectionToServer(request->port_number, request->ip_address)

    //Read from server
    //Write to client

    return;
}

 int CreateTCPConnectionToServer(uint16_t server_port_number, char * server_ip) {
    //Initialize the socket
    int server_socket_fd;
    if ((server_socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 1 ) {
        std::cout << "Unable to create TCP socket " << std::endl;
        return -1;
    }


    struct sockaddr_in server_socket_address;
    server_socket_address.sin_family = AF_INET;
    server_socket_address.sin_port = htons(server_port_number);
    memset(&(server_socket_address.sin_zero), 0, 8);

    if (inet_pton(AF_INET, server_ip, &server_socket_address.sin_addr) <= 0) {
        std::cout << "Unable to interpret server ip" << std::endl;
        return -1;
    }

    if (connect(server_socket_fd,(struct sockaddr*)&server_socket_address,sizeof(server_socket_address)) == -1) {
        std::cout << "Connection Failed " << std::endl;
        return -1;
    }
    return server_socket_fd;
}
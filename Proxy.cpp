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
    socket_address.sin_family = AF_INET;
    socket_address.sin_port = htons(port_number);
    memset(&(socket_address.sin_zero), 0, 8);


    //Bind socket (socket_fd) to port, protocol and IP (socket_address)
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

        //Set the timeout value on sockets
        struct timeval tv;
        tv.tv_sec = HTTP_REQUEST_TIMEOUT;
        tv.tv_usec = 0;
        setsockopt(new_socket_fd,SOL_SOCKET, SO_RCVTIMEO,(const char*)&tv, sizeof tv);

        std::thread thread{&Proxy::HandleConnection,this,new_socket_fd};
        thread.detach();
    }
}

void Proxy::HandleConnection(int client_socket_fd) {

    memset(buffer,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    HttpRequest http_request;

    if ((buffer_bytes = recv(client_socket_fd, buffer, BUFFER_SIZE,0)) <= 0) {
        std::cout << "Error receiving from client socket" << std::endl;
        close(client_socket_fd);
        return;
    }

    if (this->attack_mode) {
        std::thread thread_attack_mode{&Proxy::HandleAttackMode,this,client_socket_fd};
        thread_attack_mode.detach();
        return;
    }

    std::shared_ptr<HttpRequestDetails> request = http_request.parse(buffer_bytes, buffer);
    std::string ip_address = DnsResolver::Resolve(request->host_name);

    if (!request->is_valid || ip_address == "") {
        std::cout << "Invalid Request" << std::endl;
        close(client_socket_fd);
        return;
    }

    TcpConnection tcp_connection;
    int server_socket_fd = tcp_connection.Create(request->port_number, ip_address.c_str());
    if (server_socket_fd == -1) {
        std::cout << "Unable to connect to server" << std::endl;
        close(client_socket_fd);
        close(server_socket_fd);
        return;
    }

    if ((buffer_bytes = send(server_socket_fd, buffer, buffer_bytes, 0)) < 0) {
            std::cout << "Unable to forward http message to server" << std::endl;
            close(client_socket_fd);
            close(server_socket_fd);
            return;
    }
    if (this->substitution_mode) {
        std::thread thread_server_to_client{&Proxy::HandleServerToClientImageSubstitution,this,client_socket_fd, server_socket_fd};
        thread_server_to_client.detach(); 
    } else {
        std::thread thread_server_to_client{&Proxy::HandleServerToClient,this,client_socket_fd, server_socket_fd};
        thread_server_to_client.detach(); 
    }


    std::thread thread_client_to_server{&Proxy::HandleClientToServer,this,client_socket_fd, server_socket_fd, request->port_number, request->host_name};
    thread_client_to_server.detach();
    return;
}

void Proxy::HandleClientToServer(int client_socket_fd, int server_socket_fd,  int server_port_number, std::string host_name) {
    std::string prev_connection_identifier = host_name + ":" + std::to_string(server_port_number);

    char buffer_client_to_server[BUFFER_SIZE];
    memset(buffer_client_to_server,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    while ((buffer_bytes = recv(client_socket_fd, buffer_client_to_server, BUFFER_SIZE, 0)) > 0) {

        std::cout << buffer_client_to_server << std::endl;
        HttpRequest http_request;
        std::shared_ptr<HttpRequestDetails> request = http_request.parse(buffer_bytes, buffer_client_to_server);

        if (request->is_valid) {
            std::string connection_identifier = request->host_name + ":" + std::to_string(request->port_number);
            
            if (prev_connection_identifier.compare(connection_identifier) != 0) {
                close(server_socket_fd);
                std::cout << "Creating new server socket" << std::endl;
                std::string ip_address = DnsResolver::Resolve(request->host_name);
                TcpConnection tcp_connection;
                server_socket_fd = tcp_connection.Create(request->port_number, ip_address.c_str());
                if (server_socket_fd == -1) {
                    std::cout << "Unable to establish connection with new endpoint" << std::endl;
                    continue;
                }
                std::cout << "Creating new server to client" << std::endl;
                if (this->substitution_mode) {
                    std::thread thread_server_to_client{&Proxy::HandleServerToClientImageSubstitution,this,client_socket_fd, server_socket_fd};
                    thread_server_to_client.detach(); 
                } else {
                    std::thread thread_server_to_client{&Proxy::HandleServerToClient,this,client_socket_fd, server_socket_fd};
                    thread_server_to_client.detach(); 
                }

                prev_connection_identifier=connection_identifier;
            }
        }

        //Reply to server
        if ((buffer_bytes = send(server_socket_fd, buffer_client_to_server, buffer_bytes, 0)) < 0) {
            std::cout << "Unable to reply to server" << std::endl;
            break;
        } else {
            memset(buffer_client_to_server,0,BUFFER_SIZE);
            buffer_bytes = 0;
        }
    }
    close(client_socket_fd);
    std::cout << "Client connection closed" << std::endl;
}

void Proxy::HandleServerToClient(int client_socket_fd,int server_socket_fd) {
    char buffer_server_to_client[BUFFER_SIZE];
    memset(buffer_server_to_client,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    while ((buffer_bytes = recv(server_socket_fd, buffer_server_to_client, BUFFER_SIZE, 0)) > 0) {

        //Reply to client
        if ((buffer_bytes = send(client_socket_fd, buffer_server_to_client, buffer_bytes, 0)) < 0) {
            std::cout << "Unable to reply to client" << std::endl;
            break;
        } else {
            memset(buffer_server_to_client,0,BUFFER_SIZE);
            buffer_bytes = 0;
        }
    }
    close(server_socket_fd);
}

void Proxy::HandleServerToClientImageSubstitution(int client_socket_fd,int server_socket_fd) {
    std::cout << "Running Image Substitution Mode" << std::endl;
    char buffer_server_to_client[BUFFER_SIZE];
    memset(buffer_server_to_client,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    while ((buffer_bytes = recv(server_socket_fd, buffer_server_to_client, BUFFER_SIZE, 0)) > 0) {
        std::cout << "Server Has Responded" << std::endl;
        std::cout << buffer_server_to_client << std::endl;

        ImageSubstitution image_sub_utility;
        
        int response_size = image_sub_utility.responseContainsImage(buffer_server_to_client);
        if (response_size != -1 ) {//if the server is responding with an image
            //return a new response with the new image
            std::cout << "Server returning an image we need to substitute" << std::endl;
            if (image_sub_utility.fetchImage()) {
                std::cout << "Fetched Image to be substituted" << std::endl;
                if ((buffer_bytes = send(client_socket_fd, image_sub_utility.image_buffer, image_sub_utility.total_buffer_bytes, 0)) < 0) {
                    std::cout << "Unable to forward subbed image to client" << std::endl;
                    break;
                } else {
                    std::cout << "Forwarded subbed image to client" << std::endl;


                    //Drop the http message associated with the image
                    response_size -= buffer_bytes;
                    while(response_size > 0) {
                        std::cout << "Dropping useless bytes" << std::endl;
                        memset(buffer_server_to_client,0,BUFFER_SIZE);
                        buffer_bytes = recv(server_socket_fd, buffer_server_to_client, BUFFER_SIZE, 0);
                        response_size -= buffer_bytes;
                    }
                    std::cout << "Completely dropped all useless bytes" << std::endl;
                    memset(buffer_server_to_client,0,BUFFER_SIZE);
                    continue;
                }
            }
        }
        

        //Reply to client
        if ((buffer_bytes = send(client_socket_fd, buffer_server_to_client, buffer_bytes, 0)) < 0) {
            std::cout << "Unable to reply to client" << std::endl;
            break;
        } else {
            std::cout << "Responded to client" << std::endl;
            memset(buffer_server_to_client,0,BUFFER_SIZE);
            buffer_bytes = 0;
        }
    }
    close(server_socket_fd);
}

void Proxy::HandleAttackMode(int client_socket_fd) {
    std::string attack_string = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\nContent-Length:35\r\nConnection: close\r\n\r\n<html>You are being attacked</html>";

    if (send(client_socket_fd, attack_string.c_str(), attack_string.length(), 0) < 0) {
        std::cout << "Unable to reply to client" << std::endl;
        return;
    }
    close(client_socket_fd);
    return;
}
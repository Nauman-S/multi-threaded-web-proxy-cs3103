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
    memset(buffer,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    HttpRequest http_request;

    if ((buffer_bytes = recv(client_socket_fd, buffer, BUFFER_SIZE,0)) > 0) {
        printf("%s",buffer);
    } else {
        close(client_socket_fd);
        return;
    }

    if (this->attack_mode) {
        std::thread thread_attack_mode{&Proxy::HandleAttackMode,this,client_socket_fd};
        thread_attack_mode.detach();
        return;
    }

    std::shared_ptr<HttpRequestDetails> request = http_request.parse(buffer_bytes, buffer);
    if (request->is_valid) {
        std::cout << "Valid Request" << std::endl;
        std::cout << request->ip_address << std::endl;
        std::cout << request->port_number << std::endl;
        } else {
        std::cout << "Invalid Request" << std::endl;
        close(client_socket_fd);
        return;
    }

    TcpConnection tcp_connection;
    int server_socket_fd = tcp_connection.Create(request->port_number, request->ip_address.c_str());
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
        std::thread thread1{&Proxy::HandleServerToClientImageSubstitution,this,client_socket_fd, server_socket_fd};
        thread1.detach(); 
    } else {
        std::thread thread1{&Proxy::HandleServerToClient,this,client_socket_fd, server_socket_fd};
        thread1.detach(); 
    }


    std::thread thread2{&Proxy::HandleClientToServer,this,client_socket_fd, server_socket_fd};
    thread2.detach();

    // close(client_socket_fd);
    // close(server_socket_fd);
    return;
}

void Proxy::HandleClientToServer(int client_socket_fd,int server_socket_fd) {
    char buffer_client_to_server[BUFFER_SIZE];
    memset(buffer_client_to_server,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    while ((buffer_bytes = recv(client_socket_fd, buffer_client_to_server, BUFFER_SIZE, 0)) > 0) {

        //Reply to server
        if ((buffer_bytes = send(server_socket_fd, buffer_client_to_server, buffer_bytes, 0)) < 0) {
            std::cout << "Unable to reply to server" << std::endl;
            break;
        } else {
            memset(buffer_client_to_server,0,BUFFER_SIZE);
            buffer_bytes = 0;
        }
    }
}

void Proxy::HandleServerToClient(int client_socket_fd,int server_socket_fd) {
    char buffer_server_to_client[BUFFER_SIZE];
    memset(buffer_server_to_client,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    std::cout << "Waiting for server to respond " << std::endl;
    while ((buffer_bytes = recv(server_socket_fd, buffer_server_to_client, BUFFER_SIZE, 0)) > 0) {
        std::cout << "Server Has Responded" << std::endl;
        std::cout << buffer_server_to_client << std::endl;

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
}

void Proxy::HandleServerToClientImageSubstitution(int client_socket_fd,int server_socket_fd) {
    std::cout << "Running Image Substitution Mode" << std::endl;
    char buffer_server_to_client[BUFFER_SIZE];
    memset(buffer_server_to_client,0,BUFFER_SIZE);
    ssize_t buffer_bytes;
    std::cout << "Waiting for server to respond " << std::endl;
    while ((buffer_bytes = recv(server_socket_fd, buffer_server_to_client, BUFFER_SIZE, 0)) > 0) {
        std::cout << "Server Has Responded" << std::endl;
        std::cout << buffer_server_to_client << std::endl;

        ImageSubstitution image_sub_utility;
        //if the server is responding with an image
        if (image_sub_utility.responseContainsImage(buffer_server_to_client)) {
            //drop the servers response , return a new response with the new image
            std::cout << "Server returning an image we need to substitute" << std::endl;
            if (image_sub_utility.fetchImage()) {
                std::cout << "Fetched Image to be substituted" << std::endl;
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
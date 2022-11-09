#include <cstring>
#include <iostream>
#include <thread>
#include <assert.h>
//#include <cwchar>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define BACKLOG_SIZE 1

using namespace std;

void HandleConnection(int client_socket_fd) {
    char buffer[1024];
    memset(buffer,0,1024);
    ssize_t bytes_read;
    while ((bytes_read = read(client_socket_fd, buffer, 1024)) > 0) {
        printf("%s",buffer);
    }
    return;
}

int main (int argc, char **argv) {
    if (argc < 4) {
        cout << "Usage: " << argv[0] << " <port>" << "<substitution>" << "<attack>" << endl;
        exit(EXIT_FAILURE);
    }
    uint16_t port_number = atoi(argv[1]);

    // Assignment relevant code
    uint8_t image = atoi(argv[2]);
    uint8_t attacker = atoi(argv[3]);
    assert((image == 0 || image == 1) && (attacker == 0 || attacker == 1));

    //Initialize the socket
    int socket_fd;
    if ((socket_fd = socket(PF_INET, SOCK_STREAM, 0)) < 1 ) {
        cout << "Unable to create TCP socket " << endl;
        exit(EXIT_FAILURE);
    }

    // Initialize sockaddr struct - here socket is given IP, protocol and port
    struct sockaddr_in socket_address;
    socket_address.sin_family = AF_INET; // Ensure server is binding to local IP address
    socket_address.sin_port = htons(port_number);
    //wmemset(&(socket_address.sin_zero), 0, 8);


    //Bind socket (socket_fd) to port, protocl and IP (socket_address)
    if (bind(socket_fd, (struct sockaddr*)&socket_address,sizeof(socket_address))< 0) {
        cout <<"Unable to bind socket to port" << endl;
        exit(EXIT_FAILURE);
    }

    //Bind socket to listen to local port
    if (listen(socket_fd, BACKLOG_SIZE) == -1) {
        cout << "Unable to listen to connections on port " << endl;
        exit(EXIT_FAILURE);
    }

    //Accept client connections on handle them on different sockets using multithreading
    int new_socket_fd;
    for (;;) {
      
			// socklen_t clilen = sizeof client_adr;
			// newsockfd = accept(sockfd, (struct sockaddr*)& client_adr, &clilen);
			// if(newsockfd < 0) {
			// 	cout << "Error accepting connections" << endl;
			// }

			// // int and long on different platforms.
			// pthread_t thread;

			// if(pthread_create(&thread, NULL, &Proxy::beginExecution, (void*)(intptr_t)newsockfd) < 0) {
			// 	cout << "Error creating thread.. exiting" << endl;
			// 	DIE
			// }
			// count++;
			
			// pthread_detach(thread);
			// thread = NULL;

        if ((new_socket_fd = accept(socket_fd, NULL, NULL)) < 0) {
            cout << "Unable to accept client connection" << endl;
            exit(EXIT_FAILURE);
        }
        thread thread{&HandleConnection, new_socket_fd};
        thread.detach();
    }
 return 0;
}

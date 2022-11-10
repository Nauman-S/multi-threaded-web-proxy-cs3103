#ifndef PROXY_HPP
#define PROXY_HPP

#define BACKLOG_SIZE 1
#define BUFFER_SIZE 1024

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



class Proxy {

private:
    uint16_t port_number;
    char buffer[BUFFER_SIZE];
public:
    Proxy(uint16_t port_number) {
        this->port_number = port_number;
    }

    void StartProxy();
    void HandleConnection(int);
};

#endif
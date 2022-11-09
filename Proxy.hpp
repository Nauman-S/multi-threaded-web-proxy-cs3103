#ifndef PROXY_H
#define PROXY_H

#define BACKLOG_SIZE 1
#define BUFFER_SIZE 1024
#include <cstdint>

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
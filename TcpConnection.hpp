#ifndef TCP_CONNECTION_HPP
#define TCP_CONNECTION_HPP

#include <cstdint>
#include <iostream>

#include <arpa/inet.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>

class TcpConnection {
private:
public:

    /*!
        \fn int TcpConnection::Create(uint16_t server_port_number,const char * server_ip)

        Create a TCP Connection to a process identified by \a
        IPaddress and \a PortNumber.

        Return the socket file descriptor on success and -1 on failure
    */
    int Create(uint16_t,const char *);
};

#endif
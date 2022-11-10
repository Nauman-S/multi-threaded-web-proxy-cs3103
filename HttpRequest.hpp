#ifndef HTTP_REQUEST_HPP
#define HTTP_REQUEST_HPP

#include <cstdint>
#include <cstring>
#include <iostream>
#include <thread>
#include <vector>
#include <string>
#include<memory>

#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include "DnsResolver.hpp"

class HttpRequestDetails {
public:
    bool is_valid;
    uint16_t port_number;
    std::string ip_address;

    HttpRequestDetails(bool is_valid, uint16_t port_number, std::string ip_address) {
        this->is_valid = is_valid;
        this->port_number = port_number;
        this->ip_address = ip_address;
    }
};

class HttpRequest {
private:
    //const char* CRLF = "\r\n";
    char SPACE = ' ';
    char COLON = ':';
    char FORWARD_SLASH = '/';
    std::string HTTP_START= "http://";
    std::vector<std::string> methods= {"GET", "HEAD","POST","PUT", "DELETE", "TRACE", "CONNECT"};
public:
    std::shared_ptr<HttpRequestDetails> parse(ssize_t bytes_read, char * buffer);

};

#endif
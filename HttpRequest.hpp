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
#include <netinet/in.h>
#include <sys/types.h>
#include <string.h>
#include "DnsResolver.hpp"
#include <ctype.h>

class HttpRequestDetails {
public:
    bool is_valid;
    uint16_t port_number;
    std::string host_name;

    HttpRequestDetails(bool is_valid, uint16_t port_number, std::string host_name) {
        this->is_valid = is_valid;
        this->port_number = port_number;
        this->host_name = host_name;
    }
};

class HttpRequest {
private:
    char SPACE = ' ';
    char COLON = ':';
    char FORWARD_SLASH = '/';
    std::string HTTP_START= "http://";
    std::string END_OF_HTTP_HEADERS = "\r\n\r\n";
    std::vector<std::string> methods= {"GET", "HEAD","POST","PUT", "DELETE", "TRACE", "CONNECT"};
public:
    std::shared_ptr<HttpRequestDetails> parse(ssize_t bytes_read, char * buffer);

};

#endif
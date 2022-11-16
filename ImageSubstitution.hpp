#ifndef IMAGE_SUBSTITUTION_HPP
#define IMAGE_SUBSTITUTION_HPP

#define IMAGE_BUFFER_SIZE 262144

#include "HttpRequest.hpp"
#include "TcpConnection.hpp"


class ImageSubstitution {

private:
    std::string HOST_NAME = "ocna0.d2.comp.nus.edu.sg";
    std::string HTTP_REQUEST= "GET http://ocna0.d2.comp.nus.edu.sg:50000/change.jpg HTTP/1.1\r\nHost: ocna0.d2.comp.nus.edu.sg:50000\r\nAccept: image/avif,image/webp,*/*\r\nAccept-Encoding: gzip, deflate\r\nConnection: keep-alive\r\n\r\n";
    std::string CONTENT_LENGTH_HEADER = "Content-Length:";
    std::string END_OF_HTTP_HEADERS = "\r\n\r\n";
    uint16_t SERVER_PORT_NUMBER = 50000;
    char * image_start;
    char * image_end;


public:
    char image_buffer[IMAGE_BUFFER_SIZE];
    ssize_t total_buffer_bytes;

    bool fetchImage();
    int responseContainsImage(char* response);

};
#endif
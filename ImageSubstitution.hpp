#ifndef IMAGE_SUBSTITUTION_HPP
#define IMAGE_SUBSTITUTION_HPP

#include "HttpRequest.hpp"

class ImageSubstitution {

private:
    std::string HOST_NAME = "ocna0.d2.comp.nus.edu.sg";
    std::string HTTP_REQUEST= "GET http://ocna0.d2.comp.nus.edu.sg:50000/change.jpg HTTP/1.1\r\nHost: ocna0.d2.comp.nus.edu.sg:50000\r\nAccept: image/avif,image/webp,*/*\r\nAccept-Encoding: gzip, deflate";
    std::string content_length_header = "Content-Length:";
    uint16_t SERVER_PORT_NUMBER = 50000;
    char image_buffer[BUFFER_SIZE];
    char * image_start, image_end;


public:
    bool fetchImage();

};
#endif
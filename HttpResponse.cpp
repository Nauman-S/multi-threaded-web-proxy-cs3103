#include "HttpResponse.hpp"

int HttpResponse::GetContentSize( char * buffer) {
    if(strstr(buffer,END_OF_HTTP_HEADERS.c_str()) == NULL) {
        return -1;
    }

    char * buffer_ptr;

    if((buffer_ptr = strstr(buffer,CONTENT_LENGTH_HEADER.c_str())) == NULL) {
        return -1;
    }
    buffer_ptr += 16;
    std::string content_size;
    while (isdigit( *buffer_ptr )) {
        content_size.push_back(*buffer_ptr);
        buffer_ptr ++;
    }

     try {
            return std::stoi(content_size);
    } catch (...) {
            return -1;
    } 
}
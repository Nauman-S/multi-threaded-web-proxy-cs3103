#ifndef HTTP_RESPONSE_HPP
#define HTTP_RESPONSE_HPP

#include <string>
#include <cstring>

class HttpResponse {
private:
    std::string END_OF_HTTP_HEADERS = "\r\n\r\n";
    std::string CONTENT_LENGTH_HEADER = "Content-Length: ";
public:
    int GetContentSize( char * buffer);

};

#endif
#include "ImageSubstitution.hpp"
 
 bool ImageSubstitution::fetchImage() {
        memset(image_buffer,0,IMAGE_BUFFER_SIZE);

        //SET UP NON-PERSISTENT TCP CONNECTION TO SERVER WITH IMAGE
        TcpConnection conn;
        int server_socket_fd = conn.Create(SERVER_PORT_NUMBER,DnsResolver::Resolve(HOST_NAME).c_str());

        

        //REQUEST IMAGE FROM SERVER
        if (send(server_socket_fd, HTTP_REQUEST.c_str(), HTTP_REQUEST.length(), 0) < 0) {
            std::cout << "Unable to request substitution image from Server" << std::endl;
            close(server_socket_fd);
            return false;
        }


        ssize_t buffer_bytes;
        total_buffer_bytes = (buffer_bytes = 0);
        char * image_buffer_ptr = image_buffer;
        int content_length = 0;
        //PARSE IMAGE FROM RESPONSE
        while ((buffer_bytes = recv(server_socket_fd, image_buffer_ptr, IMAGE_BUFFER_SIZE, 0)) > 0) {
            total_buffer_bytes += buffer_bytes;
            if (content_length == 0) {
                if ((image_buffer_ptr = strstr(image_buffer_ptr, CONTENT_LENGTH_HEADER.c_str())) != NULL) {
                    image_buffer_ptr += 16;
                    std::string image_size;

                    while (isdigit(*image_buffer_ptr)) {
                        image_size.push_back(*image_buffer_ptr);
                        image_buffer_ptr++;
                    }
                    try {
                        content_length = std::stoi(image_size);
                    } catch (...) {
                        std::cout <<"Unable to parse Image length" << std::endl;
                        close(server_socket_fd);
                        return false;
                    }
                } else {
                    std::cout << "Unable to find content-length header in image" << std::endl;
                    return false;
                }
            }
            if ((image_buffer_ptr = strstr(image_buffer, END_OF_HTTP_HEADERS.c_str()))!= NULL) {
                image_buffer_ptr += 4;
                image_start = image_buffer_ptr;
                if ((image_start - image_buffer + content_length) <= total_buffer_bytes ) {
                    image_end = image_start + content_length;
                    close(server_socket_fd);
                    return true;
                } else {
                    image_buffer_ptr = image_buffer + total_buffer_bytes;
                }
            }
        }

        
        //TCP close
        close(server_socket_fd);
        return false;
 }

int ImageSubstitution::responseContainsImage(char* response) {
    std::string content_type_header= "\r\nContent-Type: image";
    std::string content_length_header = "\r\nContent-Length:";
    if( strstr(response,content_type_header.c_str()) == NULL ) {
        return -1;
    }
    int content_length;
    char * content_size;
    if ((content_size = strstr(response,content_length_header.c_str())) != NULL) {
        content_size += 18;
        std::string s;
        while (isdigit(*content_size )) {
            s.push_back(*content_size);
            content_size++;
        }
        try {
            content_length = std::stoi(s);
            std::cout << "Server resopnding with image of length" << std::endl;
            std::cout << content_length << std::endl;
        } catch (...) {
            std::cout <<"Unable to parse Image length" << std::endl;
            return -1;
        }
    } else {
        return -1;
    }

    char * start_of_body;
    if ((start_of_body = strstr(response,END_OF_HTTP_HEADERS.c_str())) != NULL) {
        start_of_body += 4;
        std::cout << "Total bytes to drop" << std::endl;
        std::cout <<(start_of_body-response) + content_length << std::endl;
        return (start_of_body-response) + content_length;
    }
    return -1;
 }
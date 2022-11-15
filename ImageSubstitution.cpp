
 bool ImageSubstitution::fetchImage() {
        //SET UP NON-PERSISTENT TCP CONNECTION TO SERVER WITH IMAGE
        int server_socket_fd = TcpConnection::Create(SERVER_PORT_NUMBER,DnsResolver::Resolve(host_name));

        ssize_t buffer_bytes, total_buffer_bytes;

        //1 HTTP REQUEST
        if ((buffer_bytes = send(server_socket_fd, HTTP_REQUEST.c_str(), HTTP_REQUEST.length(), 0)) < 0) {
            std::cout << "Unable to request substitution image from Server" << std::endl;
            close(client_socket_fd);
            close(server_socket_fd);
            return;
        } else if (HTTP_REQUEST.length() != buffer_bytes) {
            std::cout << "Entire request for substitution image could not be sent - hopefully server still responds" << std::endl;
        }

        total_buffer_bytes = (buffer_bytes = 0);
        char * image_buffer_ptr = image_buffer;
        int content_length = 0;
        //1 HTTP RESPOND
        while ((buffer_bytes = recv(server_socket_fd, image_buffer_ptr, BUFFER_SIZE, 0)) > 0) {
            total_buffer_bytes += buffer_bytes;
            if (content_length == 0 && ((image_buffer_ptr = strstr(image_buffer_ptr, content_length_header)) != NULL)) {
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
                std::cout << "HTTP response did not contain any substitution image";
                return false;
            }


            if ((image_buffer_ptr = strstr(image_buffer_ptr, END_OF_HTTP_HEADERS.c_str()))!= NULL) {
                image_buffer_ptr += 4;
                image_start = image_buffer_ptr;
                if ((endOfHeaders - image_buffer + content_length) == bytes_read ) {
                    image_end = endOfHeaders + content_length;
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
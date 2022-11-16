#include "HttpRequest.hpp"

std::shared_ptr<HttpRequestDetails> HttpRequest::parse(ssize_t bytes_read, char * buffer) {
    std::shared_ptr<HttpRequestDetails> output = std::make_shared<HttpRequestDetails>(false,0,"");
    int total_length = static_cast<int> (bytes_read);
    char * current_char = buffer;
    bool isValid = false;
    

    //Validate Request Method
    int index = 0;
    while (*(current_char + index) != SPACE && (current_char+index)< (current_char +total_length)) {
        index++;
    }

    for (const std::string & method: methods) {
        if (strncmp(method.c_str(),current_char,static_cast<size_t>(index)) == 0) {
            isValid = true;
        }
    }
    if (!isValid) {
        return output;
    }



    index++;
    current_char += index;


    //Validate URL
    if (strncmp(current_char,HTTP_START.c_str(),static_cast<size_t>(HTTP_START.size()))==0) {
        current_char += HTTP_START.size();
    }

    char* start_host_name = current_char;
    while (*current_char != SPACE && *current_char!=COLON && *current_char!=FORWARD_SLASH) {
        current_char ++;
    }

    std::string host_name;
    host_name.assign(start_host_name, current_char - start_host_name);
    output->host_name = host_name;
    
    if (*current_char == COLON) {
        current_char++;
        std::string port_number;
        while (isdigit(*current_char)) {
            port_number.push_back(*current_char);
            current_char++;
        }
        try {
            output->port_number = std::stoi(port_number);
        } catch (std::exception const &e) {
            return output;
        }
        
    } else {
        output->port_number = 80;
    }
    output->is_valid = true;
    return output;
}
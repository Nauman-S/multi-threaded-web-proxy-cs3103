#ifndef DNS_RESOLVER_HPP
#define DNS_RESOLVER_HPP

#include <unistd.h>
#include <string>

class DnsResolver {
public:
    static std::string Resolve(std::string host_name)
    {
        char ip_address[INET_ADDRSTRLEN];
        addrinfo hints = {};
        hints.ai_family = AF_INET;
        addrinfo * host_info = nullptr;

        if (getaddrinfo(host_name.c_str(),NULL,&hints, &host_info) != 0) {
            std::cout << "unable to resolve ip from host_name" << std::endl;
            return "";
        }

        sockaddr_in *ipv4 = reinterpret_cast<sockaddr_in *>(host_info->ai_addr);
        void * addr = &(ipv4->sin_addr);
        inet_ntop(AF_INET, addr, ip_address, INET_ADDRSTRLEN);

        freeaddrinfo(host_info); // free the linked list
        return std::string(ip_address);
    }
};

#endif
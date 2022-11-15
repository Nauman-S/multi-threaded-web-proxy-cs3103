#include  "Proxy.hpp"
#include <iostream>
#include <memory>

#include <assert.h>
#include <stdlib.h>

int main (int argc, char **argv) {
    if (argc < 4) {
        std::cout << "Usage:" << argv[0] << " <port>" << " <substitution>" << " <attack>" << std::endl;
        exit(EXIT_FAILURE);
    }
    uint16_t port_number = atoi(argv[1]);
    int image = atoi(argv[2]);
    int attacker = atoi(argv[3]);
    if (image != 0 && image != 1) {
        throw std::invalid_argument("<substitution> 1 - to enable, 0 - to disable");
    }

    if (attacker != 0 && attacker != 1) {
        throw std::invalid_argument("<attack> 1 - to enable, 0 - to disable");
    }
    std::shared_ptr<Proxy> proxy = std::make_shared<Proxy>(port_number, attacker, image);
    proxy->StartProxy();
    return 0;
}
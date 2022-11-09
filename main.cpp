#include <assert.h>
#include  "Proxy.hpp"
#include <iostream>
#include <memory>

int main (int argc, char **argv) {
    if (argc < 4) {
        std::cout << "Usage: " << argv[0] << " <port>" << "<substitution>" << "<attack>" << std::endl;
        exit(EXIT_FAILURE);
    }
    uint16_t port_number = atoi(argv[1]);
    uint8_t image = atoi(argv[2]);
    uint8_t attacker = atoi(argv[3]);

    assert((image == 0 || image == 1) && (attacker == 0 || attacker == 1));

    std::shared_ptr<Proxy> proxy = std::make_shared<Proxy>(port_number);
    proxy->StartProxy();
    return 0;
}
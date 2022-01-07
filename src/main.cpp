#include <iostream>
#include "parser.hpp"

void check_error(const std::error_code & ec);

int main() {
    const std::string path = "/Users/gvgromov/CLionProjects/pcap_parser/src/test_rcap/Corvil-13052-1636559040000000000-1636560600000000000.pcap";
    parser parser(path);
    std::error_code ec;
    parser.open(ec);
    check_error(ec);
    parser.fill_next_packet(std::cout, ec);
    check_error(ec);
    std::cout.flush();
    return 0;
}

void check_error(const std::error_code & ec) {
    if(ec) {
        std::cerr << "Error: " << ec.message() << std::endl;
        exit(1);
    }
}

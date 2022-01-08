#include <iostream>
#include <fstream>

#include "parser.hpp"

int main() {
    const std::string path = "/Users/gvgromov/Desktop/Corvil-13052-1636559040000000000-1636560600000000000.pcap";
    std::fstream out("/Users/gvgromov/CLionProjects/pcap_parser-/src/test_rcap/decode_pcap.txt");
    parser parser(path);
    std::error_code ec;
    parser.open(ec);
    while(!ec) {
        parser.fill_next_packet(out, ec);
    }
    out.flush();
    if(ec == std::errc::no_message_available) {
        return 0;
    } else {
        std::cerr << "Error: " << ec.message() << '\n';
        return -1;
    }
}

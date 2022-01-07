#include "../header_hpp/ether_header.hpp"

#include <iostream>
#include <iterator>

ether_header ether_header::read_ether_rcap_header(std::istream &stream, std::error_code & ec) {
    ether_header header{};
    stream.read(reinterpret_cast<char *>(header.ether_dhost), sizeof(header.ether_dhost));
    stream.read(reinterpret_cast<char *>(header.ether_shost), sizeof(header.ether_shost));
    stream.read(reinterpret_cast<char *>(&header.ether_type), sizeof(header.ether_type));
    if(stream.fail()) {
        ec = std::make_error_code(std::errc::io_error);
    }
    /*if(stream.eof()) {
        std doesnt have eof for error code
    }*/
    return header;
}

void ether_header::print_ether_rcap_header(std::ostream &stream, const ether_header &header) {
    stream << "Destination host: ";
    stream.setf(std::ios::hex, std::ios::basefield);
    std::copy(header.ether_dhost, header.ether_dhost + sizeof(header.ether_dhost) - 1, std::ostream_iterator<std::uint16_t>(stream, ":"));
    stream << static_cast<std::uint16_t>(header.ether_dhost[sizeof(header.ether_dhost) - 1]);
    stream << '\n' << "Source host: ";
    std::copy(header.ether_shost, header.ether_shost + sizeof(header.ether_shost) - 1, std::ostream_iterator<std::uint16_t>(stream, ":"));
    stream <<  static_cast<std::uint16_t>(header.ether_shost[sizeof(header.ether_shost) - 1]);
    stream.unsetf(std::ios::hex);
    stream << '\n' << "Protocol type: " << header.ether_type << '\n';
}

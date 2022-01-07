#include "../header_hpp/ip_header.hpp"

#include <iostream>
#include <iterator>

#include "../utility/details.hpp"

ip_header ip_header::read_ip_header(std::istream &stream, std::error_code & ec) {
    ip_header header{};
    stream.read(reinterpret_cast<char *>(&header.version), sizeof(header.version));
    // first 4 bit
    header.version = header.version >> 4;
    stream.seekg(8, std::ios::cur);//8 length
    stream.read(reinterpret_cast<char *>(&header.protocol), sizeof(header.protocol));
    stream.seekg(2, std::ios::cur);//2 length
    stream.read(reinterpret_cast<char *>(header.s_ip_address), sizeof(header.s_ip_address));
    stream.read(reinterpret_cast<char *>(header.d_ip_address), sizeof(header.d_ip_address));
    if(stream.fail()) {
        ec = std::make_error_code(std::errc::io_error);
    }
    /*if(stream.eof()) {
        std doesnt have eof for error code
    }*/
    return header;
}

void ip_header::print_ip_header(std::ostream &stream, const ip_header &header) {
    stream << "Ip version: " << static_cast<std::uint16_t>(header.version) << '\n';
    stream << "Transport protocol: ";
    if(header.protocol == static_cast<std::uint8_t>(details::transport_protocol::tcp)) {
        stream << "tcp" << '\n';
    } else if(header.protocol == static_cast<std::uint8_t>(details::transport_protocol::udp)) {
        stream << "udp" << '\n';
    }
    stream << "Source ip: ";
    std::copy(header.s_ip_address, header.s_ip_address + sizeof(header.s_ip_address) - 1, std::ostream_iterator<std::uint16_t>(stream, "."));
    stream << static_cast<std::uint16_t>(header.s_ip_address[sizeof(header.s_ip_address) - 1]);
    stream << '\n';
    stream << "Destination ip: ";
    std::copy(header.d_ip_address, header.d_ip_address + sizeof(header.d_ip_address) - 1, std::ostream_iterator<std::uint16_t>(stream, "."));
    stream << static_cast<std::uint16_t>(header.d_ip_address[sizeof(header.d_ip_address) - 1]);
    stream << '\n';
}

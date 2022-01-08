#include "../header_hpp/udp_header.hpp"

#include <iostream>

#include "../utility/details.hpp"

udp_header udp_header::read_udp_header(std::istream &stream, std::error_code & ec) {
    udp_header header{};
    stream.read(reinterpret_cast<char *>(&header.s_port), sizeof(header.s_port));
    stream.read(reinterpret_cast<char *>(&header.d_port), sizeof(header.d_port));
    stream.read(reinterpret_cast<char *>(&header.length), sizeof(header.length));
    stream.read(reinterpret_cast<char *>(&header.check_sum), sizeof(header.check_sum));
    if(stream.fail()) {
        ec = std::make_error_code(std::errc::io_error);
    }
    return header;
}

void udp_header::print_udp_header(std::ostream &stream, const udp_header &header) {
    stream << "Source port: " << details::swap_endian(header.s_port) << '\n';
    stream << "Destination port: " << details::swap_endian(header.d_port) << '\n';
    stream << "Length: " << details::swap_endian(header.length) << '\n';
    stream << "Check sum: " << details::swap_endian(header.check_sum) << '\n';
}

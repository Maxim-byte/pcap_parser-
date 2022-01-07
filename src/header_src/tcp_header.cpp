#include "../header_hpp/tcp_header.hpp"

#include <iostream>

#include "../utility/details.hpp"

tcp_header tcp_header::read_tcp_header(std::istream &stream, std::error_code & ec) {
    tcp_header header{};
    stream.read(reinterpret_cast<char *>(&header.s_port), sizeof(header.s_port));
    stream.read(reinterpret_cast<char *>(&header.d_port), sizeof(header.d_port));
    stream.seekg(details::tcp_header_length_bytes - sizeof(header.s_port) - sizeof(header.d_port), std::ios::cur);
    if(stream.fail()) {
        ec = std::make_error_code(std::errc::io_error);
    }
    /*if(stream.eof()) {
        std doesnt have eof for error code
    }*/
    return header;
}

void tcp_header::print_tcp_header(std::ostream &stream, const tcp_header &header) {
    stream << "Source port: " << details::swap_endian(header.s_port) << '\n';
    stream << "Destination port: " << details::swap_endian(header.d_port) << '\n';
}

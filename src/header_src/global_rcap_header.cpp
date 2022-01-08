#include "../header_hpp/global_rcap_header.hpp"

#include <iostream>

global_rcap_header global_rcap_header::read_global_rcap_header(std::istream & stream, std::error_code & ec) {
    global_rcap_header header{};
    stream.read(reinterpret_cast<char *>(&header.magic_number), sizeof(header.magic_number));
    stream.read(reinterpret_cast<char *>(&header.version_major), sizeof(header.version_major));
    stream.read(reinterpret_cast<char *>(&header.version_minor), sizeof(header.version_minor));
    stream.read(reinterpret_cast<char *>(&header.this_zone), sizeof(header.this_zone));
    stream.read(reinterpret_cast<char *>(&header.sigfigs), sizeof(header.sigfigs));
    stream.read(reinterpret_cast<char *>(&header.snaplen), sizeof(header.snaplen));
    stream.read(reinterpret_cast<char *>(&header.network), sizeof(header.network));

    if(stream.fail()) {
        ec = std::make_error_code(std::errc::io_error);
    }
    return header;
}

void global_rcap_header::print_global_rcap_header(std::ostream &stream, const global_rcap_header & header) {
    if(header.magic_number == static_cast<std::uint32_t>(details::bytes_order::direct)) {
        stream << "Byte order: " << "direct" << '\n';
    } else if(header.magic_number == static_cast<std::uint32_t>(details::bytes_order::swapped)) {
        stream << "Byte order: " << "reverse" << '\n';
    }
    stream << "Version: " << header.version_major << '.' << header.version_minor << '\n';
    stream << "Time zone: UTC" << std::showpos << header.this_zone << '\n';
    stream << "Accuracy of time stamps: " << header.sigfigs << '\n';
    stream << "Snapshot length: " << header.snaplen << '\n';
    stream << "LinkType: " << header.network << '\n';
}

#include "../header_hpp/packet_rcap_header.hpp"

#include <iostream>

packet_rcap_header packet_rcap_header::read_packet_rcap_header(std::istream & stream, std::error_code & ec) {
    packet_rcap_header header{};
    stream.read(reinterpret_cast<char *>(&header.timestamp_seconds), sizeof(timestamp_seconds));
    stream.read(reinterpret_cast<char *>(&header.timestamp_microseconds), sizeof(timestamp_microseconds));
    stream.read(reinterpret_cast<char *>(&header.captured_packet_length), sizeof(captured_packet_length));
    stream.read(reinterpret_cast<char *>(&header.original_packet_length), sizeof(original_packet_length));
    if(stream.fail()) {
        ec = std::make_error_code(std::errc::io_error);
    }
    return header;
}

void packet_rcap_header::print_packet_rcap_header(std::ostream &stream, const packet_rcap_header &header) {
    time_t t =  header.timestamp_seconds;
    stream << "Arrival time: " << asctime(localtime(&t));
    stream << "Epoch time: " << header.timestamp_seconds << '.' << header.timestamp_microseconds << '\n';
    stream << "Captured Packet Length: " << header.captured_packet_length << '\n';
    stream << "Original Packet Length: " << header.original_packet_length << '\n';
}

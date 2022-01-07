#pragma once

#include <cstdint>
#include <iosfwd>
#include <system_error>

struct packet_rcap_header {
    std::uint32_t timestamp_seconds;
    std::uint32_t timestamp_microseconds;
    std::uint32_t captured_packet_length;
    std::uint32_t original_packet_length;

    static packet_rcap_header read_packet_rcap_header(std::istream & stream, std::error_code & ec);
    static void print_packet_rcap_header(std::ostream & stream, const packet_rcap_header & header);
};

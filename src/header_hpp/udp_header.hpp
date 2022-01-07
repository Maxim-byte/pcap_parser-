#pragma once

#include <cstdint>
#include <iosfwd>
#include <system_error>

struct udp_header
{
    std::uint16_t s_port;
    std::uint16_t d_port;
    std::uint16_t length;
    std::uint16_t check_sum;
    static udp_header read_udp_header(std::istream & stream, std::error_code & ec);
    static void print_udp_header(std::ostream & stream, const udp_header & header);
};

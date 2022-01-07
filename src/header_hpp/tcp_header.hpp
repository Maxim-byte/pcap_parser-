#pragma once

#include <cstdint>
#include <iosfwd>
#include <system_error>

struct tcp_header
{
    std::uint16_t s_port;
    std::uint16_t d_port;

    static tcp_header read_tcp_header(std::istream & stream, std::error_code & ec);
    static void print_tcp_header(std::ostream & stream, const tcp_header & header);
};


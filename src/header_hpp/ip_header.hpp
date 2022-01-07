#pragma once

#include <cstdint>
#include <system_error>
#include <iosfwd>

struct ip_header
{
    std::uint8_t version;
    std::uint8_t protocol;
    unsigned char s_ip_address[4];
    unsigned char d_ip_address[4];

    static ip_header read_ip_header(std::istream & stream, std::error_code & ec);
    static void print_ip_header(std::ostream & stream, const ip_header & header);
};

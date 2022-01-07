#pragma once

#include <cstdint>
#include <iosfwd>
#include <system_error>

struct ether_header
{
    unsigned char ether_dhost[6];
    unsigned char ether_shost[6];
    std::uint16_t ether_type;

    static ether_header read_ether_rcap_header(std::istream & stream, std::error_code & ec);
    static void print_ether_rcap_header(std::ostream & stream, const ether_header & header);
};


#pragma once

#include <iosfwd>
#include <cstdint>
#include <system_error>

#include "../utility/details.hpp"

struct global_rcap_header {
    std::uint32_t magic_number;
    std::uint16_t version_major;
    std::uint16_t version_minor;
    std::int32_t this_zone;
    std::uint32_t sigfigs;
    std::uint32_t snaplen;
    std::uint32_t network;

    static global_rcap_header read_global_rcap_header(std::istream & stream, std::error_code & ec);
    static void print_global_rcap_header(std::ostream & stream, const global_rcap_header & header);
};

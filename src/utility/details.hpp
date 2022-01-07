#pragma once

#include <cstdint>

namespace details {
    enum class bytes_order : std::uint32_t {
        direct = 0xa1b2c3d4,
        swapped = 0xd4c3b2a1
    };
    enum class transport_protocol : std::uint8_t {
        udp = 17,
        tcp = 6
    };

    constexpr std::uint16_t swap_endian(std::uint16_t u)
    {
        return (u >> 8) | ((u & 0xFF) << 8);
    }

    constexpr std::uint8_t ip_header_length_bytes = 20;
    constexpr std::uint8_t ether_header_length_bytes = 14;
    constexpr std::uint8_t udp_header_length_bytes = 8;
    constexpr std::uint8_t tcp_header_length_bytes = 20;
}
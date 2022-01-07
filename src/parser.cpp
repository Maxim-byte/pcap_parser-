#include "parser.hpp"

#include "header_hpp/global_rcap_header.hpp"
#include "header_hpp/packet_rcap_header.hpp"
#include "header_hpp/ether_header.hpp"
#include "header_hpp/ip_header.hpp"
#include "header_hpp/udp_header.hpp"
#include "header_hpp/tcp_header.hpp"

/*
 * Parser only for direct order byte, principle is the same
 * Transfer protocol only for udp/tcp to simple it
 * Linktype only for LINKTYPE_ETHERNET 'IEEE 802.3 Ethernet (10Mb, 100Mb, 1000Mb, and up); the 10MB in the DLT_ name is historical'
 */

parser::parser(std::string_view path) : path_(path) {}

parser::~parser() {
    close();
}

void parser::open(std::error_code &error) {
    file_input_stream_.open(path_, std::ios::binary);
    if (!file_input_stream_.is_open()) {
        error = std::make_error_code(std::errc::operation_canceled);
    }
}

void parser::close() {
    if (file_input_stream_.is_open()) {
        file_input_stream_.close();
    }
}

void parser::fill_next_packet(std::ostream &file_output_stream, std::error_code &error) {
    //if first reading - read global header
    if(file_input_stream_.eof()) {
        std::exit(1);
    }
    if (file_input_stream_.tellg() == 0) {
        auto global_header = global_rcap_header::read_global_rcap_header(file_input_stream_, error);
        global_rcap_header::print_global_rcap_header(file_output_stream, global_header);
        file_output_stream << '\n';
    }
    file_output_stream << "----------------------------------------------------" << '\n';
    auto packet_header = packet_rcap_header::read_packet_rcap_header(file_input_stream_, error);
    packet_rcap_header::print_packet_rcap_header(file_output_stream, packet_header);
    file_output_stream << '\n';

    //ether layer
    auto ether_header = ether_header::read_ether_rcap_header(file_input_stream_, error);
    ether_header::print_ether_rcap_header(file_output_stream, ether_header);
    file_output_stream << '\n';

    //ip header
    auto ip_header = ip_header::read_ip_header(file_input_stream_, error);
    ip_header::print_ip_header(file_output_stream, ip_header);
    file_output_stream << '\n';

    //transport protocol
    if (ip_header.protocol == static_cast<std::uint8_t>(details::transport_protocol::udp)) {
        auto transport_header = udp_header::read_udp_header(file_input_stream_, error);
        udp_header::print_udp_header(file_output_stream, transport_header);
        file_input_stream_.seekg(
                packet_header.captured_packet_length - details::udp_header_length_bytes - details::ip_header_length_bytes
                - details::ether_header_length_bytes, std::ios::cur);
    } else if (ip_header.protocol == static_cast<std::uint8_t>(details::transport_protocol::tcp)) {
        auto transport_header = tcp_header::read_tcp_header(file_input_stream_, error);
        tcp_header::print_tcp_header(file_output_stream, transport_header);
        file_input_stream_.seekg(
                packet_header.captured_packet_length - details::tcp_header_length_bytes - details::ip_header_length_bytes
                - details::ether_header_length_bytes, std::ios::cur);
    }
    file_output_stream << "----------------------------------------------------" << '\n';
}

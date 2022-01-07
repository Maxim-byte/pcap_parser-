cmake_minimum_required(VERSION 3.20)
project(pcap_parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(pcap_parser src/main.cpp
        src/header_hpp/global_rcap_header.hpp
        src/header_src/global_rcap_header.cpp
        src/header_hpp/packet_rcap_header.hpp
        src/header_src/packet_rcap_header.cpp
        src/utility/details.hpp
        src/header_src/ether_header.cpp
        src/header_hpp/ether_header.hpp
        src/header_hpp/ip_header.hpp
        src/header_src/ip_header.cpp
        src/header_hpp/udp_header.hpp
        src/header_src/udp_header.cpp
        src/header_src/tcp_header.cpp
        src/header_hpp/tcp_header.hpp
        src/parser.cpp
        src/parser.hpp)

#pragma once

#include <fstream>
#include <string_view>
#include <string>
#include <system_error>

class parser
{
    public:
    explicit parser(std::string_view path);

    ~parser();

    void open(std::error_code & error);

    void close();

    void fill_next_packet(std::ostream & file_output_stream, std::error_code & error);

    private:
    std::size_t packet_num = 0;
    std::string path_;
    std::ifstream file_input_stream_;
};


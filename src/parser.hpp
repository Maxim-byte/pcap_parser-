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
    std::string path_;
    std::ifstream file_input_stream_;
};


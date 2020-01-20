#include "Parser.h"

std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> result;

    std::string::size_type start_pos = 0;
    std::string::size_type stop_pos = str.find_first_of(d);

    while(stop_pos != std::string::npos)
    {
        result.emplace_back(str.substr(start_pos, stop_pos - start_pos));

        start_pos = stop_pos + 1;
        stop_pos = str.find_first_of(d, start_pos);
    }

    result.emplace_back(str.substr(start_pos));

    return result;
}

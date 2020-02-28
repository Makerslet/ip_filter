#include "Parser.h"
#include <range/v3/view/split.hpp>

std::vector<std::string> split(const std::string &str, char delimeter)
{

    return  str | ranges::view::split(delimeter) | ranges::to<std::vector<std::string>>;
}

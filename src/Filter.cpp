#include "Filter.h"

std::vector<std::vector<std::string>>
    filter(const std::vector<std::vector<std::string>>& src, const std::string& elem, uint32_t position)
{
    std::vector<std::vector<std::string>> result;

    auto equal = [elem, position](const std::vector<std::string>& value) {
        if(value.size() < position)
            return false;
        return value[position] == elem;
    };
    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

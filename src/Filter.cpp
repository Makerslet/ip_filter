#include "Filter.h"

std::list<std::vector<std::string>>
    filter(const std::list<std::vector<std::string>>& src, const std::pair<std::size_t, std::string> &to_find)
{
    std::list<std::vector<std::string>> result;

    auto equal = [to_find](const std::vector<std::string>& value) {
        if(value.size() < to_find.first)
            return false;
        return value[to_find.first] == to_find.second;
    };
    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

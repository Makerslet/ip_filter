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

std::list<std::vector<std::string>>
    filter_and(const std::list<std::vector<std::string>>& src,
           const std::vector<std::pair<std::size_t, std::string>>& to_find)
{
    std::list<std::vector<std::string>> result;

    auto equal = [to_find](const std::vector<std::string>& value) {
        for(const auto& pair : to_find)
            if(value.size() < pair.first)
                return false;

        for(const auto& pair : to_find)
            if(value[pair.first] != pair.second)
                return false;

        return true;
    };
    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

std::list<std::vector<std::string>>
    filter_or(const std::list<std::vector<std::string>>& src,
           const std::vector<std::pair<std::size_t, std::string>>& to_find)
{
    std::list<std::vector<std::string>> result;

    auto equal = [to_find](const std::vector<std::string>& value) {
        for(const auto& pair : to_find)
            if(value.size() < pair.first)
                return false;

        for(const auto& pair : to_find)
            if(value[pair.first] == pair.second)
                return true;

        return false;
    };
    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

std::list<std::vector<std::string>>
    filter_any(const std::list<std::vector<std::string>>& src,
           const std::string &to_find)
{
    std::list<std::vector<std::string>> result;

    auto equal = [to_find](const std::vector<std::string>& value) {
        return std::find(value.begin(), value.end(), to_find) != value.end();
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

#include "Filter.h"
#include <iostream>

std::list<ipv4_addr> filter(const std::list<ipv4_addr> &src, const std::pair<std::size_t, unsigned char> &to_find)
{
    std::list<ipv4_addr> result;

    auto equal = [to_find](const ipv4_addr& value) {
        if(to_find.first > 3)
            return false;

        bool result = value[to_find.first] == to_find.second;
        return result;
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

std::list<ipv4_addr> filter_and(const std::list<ipv4_addr> &src,
           const std::vector<std::pair<std::size_t, unsigned char> > &to_find)
{
    std::list<ipv4_addr> result;

    auto equal = [to_find](const ipv4_addr& value) {
        for(const auto& pair : to_find)
            if(pair.first > 3)
                return false;

        for(const auto& pair : to_find)
            if(value[pair.first] != pair.second)
                return false;

        return true;
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

std::list<ipv4_addr> filter_or(std::list<ipv4_addr> &src,
           const std::vector<std::pair<std::size_t, unsigned char> > &to_find)
{
    std::list<ipv4_addr> result;

    auto equal = [to_find](const ipv4_addr& value) {
        for(const auto& pair : to_find)
            if(pair.first > 3)
                return false;

        for(const auto& pair : to_find)
            if(value[pair.first] == pair.second)
                return true;

        return false;
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

std::list<ipv4_addr> filter_any(std::list<ipv4_addr> &src,
           unsigned char to_find)
{
    std::list<ipv4_addr> result;

    auto equal = [to_find](const ipv4_addr& value) {
        return value.contains(to_find);
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

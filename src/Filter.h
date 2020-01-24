#ifndef FILTER_H
#define FILTER_H

#include "IpAddr.h"

#include <list>
#include <algorithm>

template <std::size_t N>
std::list<ip_addr<N>>
    filter(const std::list<ip_addr<N>>& src,
           const std::pair<std::size_t, unsigned char>& to_find) {

    std::list<ip_addr<N>> result;

    auto equal = [to_find](const ip_addr<N>& value) {
        if(to_find.first >= ip_addr<N>::num_components)
            return false;

        bool result = value[to_find.first] == to_find.second;
        return result;
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

template <std::size_t N>
std::list<ip_addr<N>>
    filter_and(const std::list<ip_addr<N>>& src,
           const std::vector<std::pair<std::size_t, unsigned char>>& to_find) {

    std::list<ip_addr<N>> result;

    auto equal = [to_find](const ip_addr<N>& value) {
        for(const auto& pair : to_find)
            if(pair.first > ip_addr<N>::num_components)
                return false;

        for(const auto& pair : to_find)
            if(value[pair.first] != pair.second)
                return false;

        return true;
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

template <std::size_t N>
std::list<ip_addr<N>>
    filter_or(std::list<ip_addr<N>>& src,
           const std::vector<std::pair<std::size_t, unsigned char>>& to_find) {

    std::list<ip_addr<N>> result;

    auto equal = [to_find](const ip_addr<N>& value) {
        for(const auto& pair : to_find)
            if(pair.first > ip_addr<N>::num_components)
                return false;

        for(const auto& pair : to_find)
            if(value[pair.first] == pair.second)
                return true;

        return false;
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

template <std::size_t N>
std::list<ip_addr<N>>
    filter_any(std::list<ip_addr<N>>& src, unsigned char to_find) {

    std::list<ip_addr<N>> result;

    auto equal = [to_find](const ip_addr<N>& value) {
        return value.contains(to_find);
    };

    std::copy_if(src.begin(), src.end(), std::back_inserter(result), equal);

    return result;
}

#endif // FILTER_H

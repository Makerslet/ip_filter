#ifndef FILTER_H
#define FILTER_H

#include "IpAddr.h"
#include "Utils.h"

#include <range/v3/view/filter.hpp>

class Filter {
public:
template <std::size_t N, typename Container>
static Container filter(const Container& src,
           const Utils::Condition& condition) {

    Utils::find_one_func<N> func(condition);
    return src | ranges::view::filter(func) | ranges::to<Container>;
}

template <std::size_t N, typename Container>
static Container filter_and(const Container& src,
            const std::vector<Utils::Condition>& conditions) {

    std::vector<Utils::find_one_func<N>> functors;
    for(const auto& value : conditions)
        functors.emplace_back(value);

    auto and_lambda = [functors](const ip_addr<4>& ip){
        for(const auto& elem : functors)
            if(!elem(ip))
                return false;
        return true;
    };

    return src | ranges::view::filter(and_lambda) | ranges::to<Container>;
}

template <std::size_t N, typename Container>
static Container filter_any(const Container& src,
            unsigned char condition) {

    auto find_any = [condition](const ip_addr<4>& ip) {return ip.contains(condition);};
    return  src | ranges::view::filter(find_any) | ranges::to<Container>;
}

};

#endif // FILTER_H
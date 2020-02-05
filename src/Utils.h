#ifndef UTILS_H
#define UTILS_H

#include "IpAddr.h"
#include "Parser.h"

#include <cstddef>
#include <iostream>
#include <vector>
#include <range/v3/algorithm/for_each.hpp>

class Utils
{
public:
    template<std::size_t N>
    static std::vector<ip_addr<N>> read_ip_from_input() {
        std::vector<ip_addr<N>> ip_pool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> tokens = split(line, '\t');
            if(tokens.size() > 0)
            {
                std::vector<std::string> ip = split(tokens[0], '.');
                if(ip.size() == N)
                    ip_pool.emplace_back(std::move(ip));
            }
        }

        return ip_pool;
    }

    template <std::size_t N>
    struct find_one_func {
        explicit find_one_func(std::pair<std::size_t, unsigned char> s_elem) :
            search_elem(s_elem){}

        bool operator()(const ip_addr<N>& ip) const {
            if(search_elem.first >= ip_addr<N>::num_components)
                return false;
            return  ip[search_elem.first] == search_elem.second;
        }

        std::pair<std::size_t, unsigned char> search_elem;
    };

    static inline auto reverse_comparator = [](const ip_addr<4>& lhs, const ip_addr<4>& rhs) { return rhs < lhs; };
    static inline auto print = [](const auto& ip) {std::cout << ip.to_str() << std::endl;};

};

#endif // UTILS_H

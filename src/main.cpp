#include "IpAddr.h"
#include "Filter.h"
#include "Parser.h"

#include <iostream>
#include <list>

int main (int, char **)
{
    std::list<ipv4_addr> ip_pool;
    for(std::string line; std::getline(std::cin, line);)
    {
        std::vector<std::string> tokens = split(line, '\t');
        if(tokens.size() > 0)
        {
            std::vector<std::string> ip = split(tokens[0], '.');
            if(ip.size() == 4)
                ip_pool.emplace_back(std::move(ip));
        }
    }

    auto reverse_comparator = [](const ipv4_addr& lhs, const ipv4_addr& rhs) { return rhs < lhs; };

    ip_pool.sort(reverse_comparator);
    for(const ipv4_addr& ip : ip_pool)
        std::cout<< ip << std::endl;

    auto result_simple_filter = filter(ip_pool, {0, 1});
    for(const ipv4_addr& ip : result_simple_filter)
        std::cout<< ip << std::endl;

    auto result_and_filter = filter_and(ip_pool, {{0, 46},{1, 70}});
    for(const ipv4_addr& ip : result_and_filter)
        std::cout<< ip << std::endl;

    auto result_any_filter = filter_any(ip_pool, 46);
    for(const ipv4_addr& ip : result_any_filter)
        std::cout << ip << std::endl;

    return 0;
}



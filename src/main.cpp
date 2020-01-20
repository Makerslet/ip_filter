#include <iostream>
#include <list>
#include "Filter.h"
#include "Parser.h"

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& obj) {
    if(obj.size() == 0)
        return os;

    std::size_t index = 0;
    while(index < obj.size() - 1)
        os << obj[index++] << ".";
    os << obj[index];

    return os;
}

int main (int, char **)
{
    std::list<std::vector<std::string>> ip_pool;
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

    ip_pool.sort(std::greater<std::vector<std::string>>());
    for(const std::vector<std::string>& ip : ip_pool)
        std::cout<< ip << std::endl;

    auto result_simple_filter = filter(ip_pool, {0, "1"});
    for(const std::vector<std::string>& ip : result_simple_filter)
        std::cout<< ip << std::endl;

    auto result_and_filter = filter_and(ip_pool, {{0, "46"},{1, "70"}});
    for(const std::vector<std::string>& ip : result_and_filter)
        std::cout<< ip << std::endl;

    auto result_any_filter = filter_any(ip_pool, "46");
    for(const std::vector<std::string>& ip : result_any_filter)
        std::cout << ip << std::endl;

    return 0;
}



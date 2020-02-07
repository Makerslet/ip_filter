#include "IpAddr.h"
#include "Filter.h"
#include "Utils.h"

#include <range/v3/action/sort.hpp>


int main (int, char **)
{
    std::vector<ip_addr<4>> ip_pool(Utils::read_ip_from_input<4>());

    ranges::actions::sort(ip_pool, Utils::reverse_comparator);

    Utils::print_all(std::cout, ip_pool);
    Utils::print_all(std::cout, Filter::filter<4>(ip_pool, {0, 1}));
    Utils::print_all(std::cout, Filter::filter_and<4>(ip_pool, {{0, 46}, {1, 70}}));
    Utils::print_all(std::cout, Filter::filter_any<4>(ip_pool, 46));


    return 0;
}



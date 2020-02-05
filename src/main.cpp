#include "IpAddr.h"
#include "Utils.h"

#include <range/v3/action/sort.hpp>
#include <range/v3/view/filter.hpp>
#include <range/v3/algorithm/for_each.hpp>
#include <range/v3/algorithm/find.hpp>


int main (int, char **)
{
    std::vector<ip_addr<4>> ip_pool(Utils::read_ip_from_input<4>());


    ranges::actions::sort(ip_pool, Utils::reverse_comparator);
    ranges::for_each(ip_pool, Utils::print);


    Utils::find_one_func<4> f1({0, 1});
    auto result_simple_filter = ip_pool | ranges::view::filter(f1);
    ranges::for_each(result_simple_filter, Utils::print);


    Utils::find_one_func<4> f2({0, 46});
    Utils::find_one_func<4> f3({1, 70});
    auto and_lambda = [f2, f3](const ip_addr<4>& ip){ return  f2(ip) && f3(ip);};
    auto result_and_filter = ip_pool | ranges::view::filter(and_lambda);
    ranges::for_each(result_and_filter, Utils::print);


    auto find_any = [](const ip_addr<4>& ip) {return ip.contains(46);};
    auto result_any_filter = ip_pool | ranges::view::filter(find_any);
    ranges::for_each(result_any_filter, Utils::print);

    return 0;
}



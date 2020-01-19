#include <iostream>
#include <vector>
#include "Filter.h"

int main (int, char **)
{
    std::vector<std::vector<std::string>> ips = {
        {std::vector<std::string>{"113","162","145","156"}},
        {std::vector<std::string>{"79","180","73","190"}},
        {std::vector<std::string>{"179","210","145","4"}},
        {std::vector<std::string>{"219","102","120","135"}},
        {std::vector<std::string>{"67","232","81","208"}},
    };

    std::sort(ips.begin(), ips.end());
    auto result = filter(ips, "67", 0);
}

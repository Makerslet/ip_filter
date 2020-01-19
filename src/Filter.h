#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <string>
#include <algorithm>

std::vector<std::vector<std::string>>
    filter(const std::vector<std::vector<std::string>>& src, const std::string& elem, uint32_t position);

#endif // FILTER_H

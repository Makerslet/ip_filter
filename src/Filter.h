#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>

std::list<std::vector<std::string>>
    filter(const std::list<std::vector<std::string>>& src,
           const std::pair<std::size_t, std::string>& to_find);

std::list<std::vector<std::string>>
    filter_and(const std::list<std::vector<std::string>>& src,
           const std::vector<std::pair<std::size_t, std::string>>& to_find);

std::list<std::vector<std::string>>
    filter_or(const std::list<std::vector<std::string>>& src,
           const std::vector<std::pair<std::size_t, std::string>>& to_find);

std::list<std::vector<std::string>>
    filter_any(const std::list<std::vector<std::string>>& src,
           const std::pair<std::size_t, std::string>& to_find);

#endif // FILTER_H

#ifndef FILTER_H
#define FILTER_H

#include <vector>
#include <list>
#include <string>
#include <algorithm>
#include "IpAddr.h"

std::list<ipv4_addr>
    filter(const std::list<ipv4_addr>& src,
           const std::pair<std::size_t, unsigned char>& to_find);

std::list<ipv4_addr>
    filter_and(const std::list<ipv4_addr>& src,
           const std::vector<std::pair<std::size_t, unsigned char>>& to_find);

std::list<ipv4_addr>
    filter_or(std::list<ipv4_addr>& src,
           const std::vector<std::pair<std::size_t, unsigned char>>& to_find);

std::list<ipv4_addr>
    filter_any(std::list<ipv4_addr>& src, unsigned char to_find);

#endif // FILTER_H

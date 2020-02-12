#include "IpAddr.h"

#include <sstream>

template<>
std::string ip_addr<4>::to_str() const
{
    std::string result;

    for(unsigned char value : _numbersIp)
        result += std::to_string(value) + ".";

    // remove last point
    result.erase(result.size() - 1, 1);
    return result;
}

template<>
std::string ip_addr<16>::to_str() const
{
    std::stringstream sstream;
    sstream << std::hex;

    std::size_t index = 0;
    while(index < 16)
    {
        sstream << std::to_string(_numbersIp[index++]);
        if(index % 2 == 0)
            sstream << ":";
    }

    return  sstream.str();
}


#include "IpAddr.h"

#include <stdexcept>
#include <algorithm>

ipv4_addr::ipv4_addr(const std::vector<std::string>& ip_tokens)
{
    if(ip_tokens.size() != ipv4_addr::num_components())
        throw std::invalid_argument("wrong num tokens");

    _numbersIp = toIntArray(ip_tokens);
    _strView = toString(ip_tokens);
}

std::array<unsigned char, 4> ipv4_addr::toIntArray(const std::vector<std::string>& tokens) const
{
    std::array<unsigned char, 4> result;

    for(std::size_t index = 0; index < ipv4_addr::num_components(); ++index)
    {
        int result_int = std::stoi(tokens[index]);
        if(result_int < 0 || result_int > 255)
            throw std::invalid_argument("token out of range");

        result[index] = static_cast<unsigned char>(result_int);
    }

    return  result;
}

std::string ipv4_addr::toString(const std::vector<std::string>& tokens) const
{
    std::string result;

    for(const std::string& token : tokens)
        result += token + ".";

    // remove last point
    result.erase(result.size() - 1, 1);
    return result;
}

bool ipv4_addr::operator<(const ipv4_addr& rhs) const
{
    return _numbersIp < rhs._numbersIp;
}

bool ipv4_addr::operator>(const ipv4_addr& rhs) const
{
    return _numbersIp > rhs._numbersIp;
}

bool ipv4_addr::operator==(const ipv4_addr& rhs) const
{
    return _numbersIp == rhs._numbersIp;
}

bool ipv4_addr::operator!=(const ipv4_addr& rhs) const
{
    return _numbersIp != rhs._numbersIp;
}

unsigned char ipv4_addr::operator[](std::size_t index) const
{
    return _numbersIp.at(index);
}

bool ipv4_addr::empty() const
{
    return _strView.empty();
}

bool ipv4_addr::contains(unsigned char value) const
{
    if(empty())
        return false;

    return std::find(_numbersIp.cbegin(), _numbersIp.cend(), value) != _numbersIp.cend();
}

std::size_t ipv4_addr::num_components()
{
    return 4;
}


std::ostream& operator<<(std::ostream& os, const ipv4_addr& obj)
{
    os << obj._strView;
    return  os;
}

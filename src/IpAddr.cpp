#include "IpAddr.h"
#include <stdexcept>
#include <algorithm>

ipv4_addr::ipv4_addr(const std::vector<std::string>& ip_tokens)
{
    if(ip_tokens.size() != 4)
        return;

    // при конвертации токенов может вылететь exception
    try {
        _numbersIp = toIntArray(ip_tokens);
    } catch (std::invalid_argument&) { return; }

    _strView = toString(ip_tokens);
}

std::array<unsigned char, 4> ipv4_addr::toIntArray(const std::vector<std::string>& tokens) const
{
    std::array<unsigned char, 4> result;

    for(std::size_t index = 0; index < 4; ++index)
    {
        int result_int = std::stoi(tokens[index]);
        if(result_int < 0 || result_int > 255)
            throw std::invalid_argument("");

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
    if(empty() || rhs.empty())
        return false;

    for(std::size_t index = 0; index < 4; ++index)
    {
        if(_numbersIp[index] == rhs._numbersIp[index])
            continue;
        else
            return _numbersIp[index] < rhs._numbersIp[index];
    }

    return false;
}

unsigned char ipv4_addr::operator[](std::size_t index) const
{
    if(empty())
        return 0;

    if(index > 3)
        return  0;

    return _numbersIp[index];
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


std::ostream& operator<<(std::ostream& os, const ipv4_addr& obj)
{
    os << obj._strView;
    return  os;
}

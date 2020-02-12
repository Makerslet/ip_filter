#ifndef IPADDR_H
#define IPADDR_H

#include <array>
#include <string>
#include <vector>
#include <algorithm>
#include <functional>

template<std::size_t N>
class ip_addr {
public:
    explicit ip_addr(const std::vector<std::string>& ip_tokens) {
        static_assert (N == 4 || N == 16, "wrong num bytes in ip address");

        if(ip_tokens.size() != N)
            throw std::invalid_argument("wrong num tokens");

        _numbersIp = to_int_array(ip_tokens);
    }

    bool contains(unsigned char value) const {
        return std::find(_numbersIp.cbegin(), _numbersIp.cend(), value) != _numbersIp.cend();
    }

    bool operator<(const ip_addr& rhs) const {
        return _numbersIp < rhs._numbersIp;
    }

    bool operator>(const ip_addr& rhs) const {
        return _numbersIp > rhs._numbersIp;
    }

    bool operator==(const ip_addr& rhs) const {
        return _numbersIp == rhs._numbersIp;
    }

    bool operator!=(const ip_addr& rhs) const {
        return _numbersIp != rhs._numbersIp;
    }

    unsigned char operator[](std::size_t index) const {
        return _numbersIp.at(index);
    }

    static constexpr size_t num_components = N;
    std::string to_str() const;

private:
    std::array<unsigned char, N> to_int_array(const std::vector<std::string>& tokens) const {

        std::array<unsigned char, N> result;

        const int base = num_components == 4 ? 10 : 16;
        for(std::size_t index = 0; index < N; ++index)
        {
            int result_int = std::stoi(tokens[index], nullptr, base);
            if(result_int < 0 || result_int > 255)
                throw std::invalid_argument("token out of range");

            result[index] = static_cast<unsigned char>(result_int);
        }

        return  result;
    }

private:
    std::array<unsigned char, N> _numbersIp;
};

#endif // IPADDR_H

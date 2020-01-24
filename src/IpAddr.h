#ifndef IPADDR_H
#define IPADDR_H

#include <array>
#include <string>
#include <vector>

class ipv4_addr
{
public:
    explicit ipv4_addr(const std::vector<std::string>&);
    bool empty() const;
    bool contains(unsigned char) const;

    static std::size_t num_components();

    bool operator<(const ipv4_addr& rhs) const;
    bool operator>(const ipv4_addr& rhs) const;
    bool operator==(const ipv4_addr& rhs) const;
    bool operator!=(const ipv4_addr& rhs) const;
    unsigned char operator[](std::size_t index) const;
    friend std::ostream& operator<<(std::ostream& os, const ipv4_addr& obj);

private:
    std::array<unsigned char, 4> toIntArray(const std::vector<std::string>&) const;
    std::string toString(const std::vector<std::string>&) const;

private:
    std::string _strView;
    std::array<unsigned char, 4> _numbersIp;
};

std::ostream& operator<<(std::ostream& os, const ipv4_addr& obj);

#endif // IPADDR_H

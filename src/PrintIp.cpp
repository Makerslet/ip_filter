#include "PrintIp.h"

std::ostream& operator<<(std::ostream& os, const std::vector<std::string>& obj) {
    if(obj.size() == 0)
        return os;

    std::size_t index = 0;
    while(index < obj.size() - 1)
        os << obj[index++] << ".";
    os << obj[index];

    return os;
}

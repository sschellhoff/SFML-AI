#include "mercer/Misc/StringUtils.hpp"

namespace mercer {

std::vector<std::string> splitString(const std::string &data, const std::string &delimiter) {
    std::vector<std::string> result;

    size_t pos = 0;
    size_t last = 0;
    size_t next = 0;
    while((next = data.find(delimiter, last)) != std::string::npos) {
        auto part = data.substr(last, next-last);
        last = next + 1;
        if(part.length() != 0) {
            result.push_back(part);
        }
    }
    auto last_part = data.substr(last);
    if(last_part.length() != 0) {
        result.push_back(last_part);
    }

    return result;
}

bool compare(const std::string &s1, const std::string &s2) {
    return s1.compare(s2) == 0;
}

}
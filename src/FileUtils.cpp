#include "mercer/Misc/FileUtils.hpp"

#include <fstream>
#include <streambuf>

namespace mercer {

std::string loadTextFile(const std::string &path) {
    std::ifstream t(path);
    return std::string((std::istreambuf_iterator<char>(t)),
                        std::istreambuf_iterator<char>());
}

}
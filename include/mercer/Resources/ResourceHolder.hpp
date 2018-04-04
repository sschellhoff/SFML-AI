/*
MIT License

Copyright (c) 2018 Sören Schellhoff

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#pragma once

#include <map>
#include <memory>
#include <string>

namespace mercer {

template <typename R, typename K=std::string>
class ResourceHolder {
private:
    std::map<K, std::unique_ptr<R>> data;
public:
    ResourceHolder();
    void add(const K &key, const std::string &path);
    R &get(const K &key);
    const R &get(const K &key) const;
    R &operator[](const K &key);
    const R &operator[](const K &key) const;
    bool hasKey(const K &key) const;
};

template <typename R, typename K=std::string>
ResourceHolder::ResourceHolder() {
}

template <typename R, typename K=std::string>
void ResourceHolder::add(const K &key, const std::string &path) {
    if(!hasKey(key)) {
        (data[key] = std::make_unique<R>()).loadFromFile(path);
    } else {
    }
}

template <typename R, typename K=std::string>
R &ResourceHolder::get(const K &key) {
    return data.get(key);
}

template <typename R, typename K=std::string>
const R &ResourceHolder::get(const K &key) const {
    return data.get(key);
}

template <typename R, typename K=std::string>
R &ResourceHolder::operator[](const K &key) {
    return data.get(key);
}

template <typename R, typename K=std::string>
const R &ResourceHolder::operator[](const K &key) const {
    return data.get(key);
}

template <typename R, typename K=std::string>
bool ResourceHolder::hasKey(const K &key) const {
    return data.find(key) != data.end();
}

}
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

#include <vector>
#include <cstddef>
#include <string>
#include <sstream>

namespace mercer {

template <typename BlockType = unsigned int>
class Bitset {
public:
    using size_type = std::size_t;
private:
    std::vector<BlockType> data;
    const size_type block_size;

    size_type getBlockNo(size_type position) const {
        return position / block_size;
    }
    size_type getPositionInBlock(size_type position) const {
        return position % block_size;
    }
public:
    explicit Bitset(size_type initial_size = 1) : data(initial_size, false), block_size(sizeof(BlockType) * 8) {
    }

    size_type getBlockSize() const {
        return block_size;
    }

    void resize(size_type num_blocks, bool value = false) {
        data.resize(num_blocks, value);
    }
    void clear() {
        data.clear();
    }
    void push_back(BlockType block) {
        data.push_back(block);
    }

    Bitset &operator&=(const Bitset &bitset);
    Bitset &operator|=(const Bitset &bitset);
    Bitset &operator^=(const Bitset &bitset);
    Bitset &operator-=(const Bitset &bitset);

    Bitset &operator~() const;

    Bitset &setValue(size_type position, bool value) {
        auto block = getBlockNo(position);
        auto position_in_block = getPositionInBlock(position);
        if(value) {
            data[block] |= (1 << position_in_block);
        } else {
            data[block] &= ~(1 << position_in_block);
        }
        return *this;
    }
    Bitset &setAllBits(bool value) {
        auto initial_size = data.size();
        data.clear();
        if(value) {
            data.resize(initial_size, ~0);
        } else {
            data.resize(initial_size, 0);
        }
        return *this;
    }
    

    Bitset &set(size_type position) {
        return setValue(position, true);
    }
    Bitset &set() {
        return setAllBits(true);
    }
    Bitset &reset(size_type position) {
        return setValue(position, false);
    }
    Bitset &reset() {
        return setAllBits(false);
    }
    Bitset &flip(size_type position) {
        auto block = getBlockNo(position);
        auto position_in_block = getPositionInBlock(position);
        data[block] ^= (1 << position_in_block);
        return *this;
    }
    Bitset &flip() {
        for(auto &block : data) {
            block ^= ~0;
        }
        return *this;
    }

    bool get(size_type position) const {
        auto block = getBlockNo(position);
        auto position_in_block = getPositionInBlock(position);
        return (data[block] & (1 << position_in_block)) != 0;
    }
    bool any() const {
        return !none();
    }
    bool none() const {
        for(auto &block : data) {
            if(block != 0) {
                return false;
            }
        }
        return true;
    }
    bool all() const {
        for(auto &block : data) {
            if(~block != 0) {
                return false;
            }
        }
        return true;
    }

    size_type size() const {
        return numBlocks() * block_size;
    }
    size_type numBlocks() const {
        return data.size();
    }
    bool empty() const {
        return data.empty();
    }

    size_type getFirst() const {
        for(size_type block = 0; block < numBlocks(); block++) {
            if(data[block] != 0) {
                for(size_type position = 0; position < block_size; position++) {
                    if((data[block] & (1 << position)) != 0) {
                        return block * block_size + position;
                    }
                }
            }
        }
        return size();
    }

    size_type getNext(size_type position) const {
        auto initial_block = getBlockNo(position);
        auto position_in_block = getPositionInBlock(position);
        for(size_type block = initial_block; block < numBlocks(); block++) {
            if(data[block] != 0) {
                for(size_type pos = (block == initial_block) ? position_in_block : 0; pos < block_size; pos++) {
                    if((data[block] & (1 << pos)) != 0) {
                        return block * block_size + pos;
                    }
                }
            }
        }
        return size();
    }

    std::vector<size_type> getSet() const {
        std::vector<size_type> result;
        for(auto idx = getFirst(); idx < size() && get(idx); idx = getNext(idx + 1)) {
            result.push_back(idx);
        }
        return result;
    }

    bool includes(const Bitset &other) const {
        if(numBlocks() == other.numBlocks()) {
            for(auto i = 0; i < numBlocks(); i++) {
                if((data[i] & other.data[i]) != other.data[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    bool excludes(const Bitset &other) const {
        if(numBlocks() == other.numBlocks()) {
            for(auto i = 0; i < numBlocks(); i++) {
                if((data[i] & other.data[i]) != 0) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    std::string toString() const {
        if(empty()) {
            return "";
        }
        std::stringstream result;
        for(size_type position = 0; position < size(); position++) {
            result << (get(position) ? "1" : "0");
        }
        return result.str();
    }
};

template <typename BlockType>
bool operator==(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
bool operator!=(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
bool operator<(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
bool operator>(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
bool operator<=(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
bool operator>=(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
Bitset<BlockType> operator&(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
Bitset<BlockType> operator|(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
Bitset<BlockType> operator^(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

template <typename BlockType>
Bitset<BlockType> operator-(const Bitset<BlockType> &a, const Bitset<BlockType> &b);

}
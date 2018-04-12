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

namespace mercer {

template <typename BlockType = unsigned int>
class Bitset {
public:
    using size_type = std::size_t;
private:
    std::vector<BlockType> data;

    size_type getBlockNo(size_type position) const {
        return position / block_size;;
    }
    size_type getPositionInBlock(size_type position) const {
        return position % block_size;
    }
public:
    size_type block_size;

    explicit Bitset(size_type initial_size = 0) : data(initial_size, false), block_size(sizeof(BlockType)) {
    }

    void resize(size_type num_bits, bool value = false) {
        data.resize(num_bits, value);
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

    Bitset &set(size_type position, bool value = true) {
        auto block = getBlockNo(position);
        auto position_in_block = getPositionInBlock(position);
        if(value) {
            data[block] |= (1 << position_in_block);
        } else {
            data[block] &= ~(1 << position_in_block);
        }
        return *this;
    }
    Bitset &set(bool value = true) {
        auto initial_size = data.size();
        data.clear();
        if(value) {
            data.resize(initial_size, ~0);
        } else {
            data.resize(initial_size, 0);
        }
        return *this;
    }
    Bitset &reset(size_type position) {
        set(position, false);
        return *this;
    }
    Bitset &reset() {
        set(false);
        return *this;
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
    bool any(size_type position) const {
        return !none();
    }
    bool none(size_type position) const {
        for(auto &block : data) {
            if(block != 0) {
                return false;
            }
        }
        return true;
    }
    bool all(size_type position) const {
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
        for(size_type block; block < data.size(); block++) {
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
        for(size_type block = initial_block; block < data.size(); block++) {
            if(block != 0) {
                for(size_type pos = (block == initial_block) ? position_in_block : 0; pos < block_size; pos++) {
                    if((data[block] & (1 << pos)) != 0) {
                        return block * block_size + pos;
                    }
                }
            }
        }
        return size();
    }

    std::string toString() const {
        return "";
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
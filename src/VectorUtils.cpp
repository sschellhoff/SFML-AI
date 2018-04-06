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

#include "mercer/Misc/VectorUtils.hpp"
#include <cmath>

namespace mercer {

float vector_length_squared(const sf::Vector2f &vector) {
    return vector.x * vector.x + vector.y * vector.y;
}

float vector_length(const sf::Vector2f &vector) {
    auto length_squared = vector_length_squared(vector);
    return sqrt(length_squared);
}

sf::Vector2f process_deadzone(sf::Vector2f vector, float deadzone) {
    auto length_squared = vector_length_squared(vector);
    return (length_squared >= deadzone) ? vector : ((length_squared <= -deadzone) ? vector : sf::Vector2f{});
}

sf::Vector2f get_normalized(const sf::Vector2f &vector) {
    auto sqrt_length = vector_length_squared(vector);
    auto one_div_length = static_cast<float>(sqrt(1.f / sqrt_length));
    return sf::Vector2f{vector.x * one_div_length, vector.y * one_div_length};
}

}
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
#include <vector>
#include <algorithm>

namespace mercer {

template <typename S>
class StateGraph {
public:
    using STATE_TYPE = std::size_t;
private:
    STATE_TYPE current_state;
    std::vector<std::map<S, STATE_TYPE>> delta;
public:
    StateGraph() {
    }

    StateGraph(const std::size_t initial_size) : delta(initial_size) {
    }

    void addTransition(const STATE_TYPE start_state, const S input, const STATE_TYPE target_state) {
        if(delta.capacity() <= start_state) {
            const auto min_capacity = std::min(start_state * 2, 8UL);
            delta.resize(min_capacity);
        }
        delta[start_state][input] = target_state;
    }

    bool hasTransition(const STATE_TYPE start_state, const S input) const {
        if(delta.size() <= start_state) {
            return false;
        }
        const auto &transitions = delta[start_state];
        if(transitions.empty()) {
            return false;
        }
        const auto result = transitions.find(input) != transitions.end();
        return result;
    }

    bool hasTransition(const S input) const {
        return hasTransition(current_state, input);
    }

    void setCurrentState(STATE_TYPE state) {
        current_state = state;
    }

    const STATE_TYPE getCurrentState() const {
        return current_state;
    }

    const STATE_TYPE calculateDelta(const STATE_TYPE start_state, const S input) const {
        return delta[start_state].at(input);
    }

    const STATE_TYPE calculateDelta(const S input) const {
        return calculateDelta(current_state, input);
    }

    const STATE_TYPE computeInput(const STATE_TYPE start_state, const S input) {
        current_state = calculateDelta(start_state, input);
        return current_state;
    }

    const STATE_TYPE computeInput(const S input) {
        return computeInput(current_state, input);
    }
};

}
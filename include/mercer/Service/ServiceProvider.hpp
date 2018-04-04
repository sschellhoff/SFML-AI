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

#include <memory>
#include <type_traits>
#include "BaseService.hpp"

namespace mercer {

template <typename T>
class ServiceProvider {
    static_assert(std::is_base_of<BaseService, T>::value);
private:
    ServiceProvider() {}
    static std::unique_ptr<T> service;
public:
    static void provide(std::unique_ptr<T> service) {
        ServiceLocator::service = std::move<>(service);
    }
    template<typename... Args>
    static void provideType(Args&&... args) {
        provide(std::make_unique<T>(std::forward<Args>(args)...));
    }
    static T &getService() {
        return *(ServiceLocator::service.get());
    }
};

template <typename T>
std::unique_ptr<T> ServiceLocator<T>::service;

}
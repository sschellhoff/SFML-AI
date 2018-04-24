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

#include "ECS.hpp"
#include <vector>
#include <type_traits>
#include "ComponentBitmask.hpp"
#include "ComponentBase.hpp"
#include "EntityID.hpp"

namespace mercer {

class SystemBase {
private:
    ECS *ecs;
    Bitmask required;
    Bitmask excluded;
    std::vector<EntityID> entities;
    bool marked_to_remove;

protected:
    template<typename T>
    void requires() {
        static_assert(std::is_base_of<ComponentBase, T>::value);
        required.set(T::GetId());
    }

    template<typename T>
    void excludes() {
        static_assert(std::is_base_of<ComponentBase, T>::value);
        excluded.set(T::GetId());
    }

    virtual void process(Entity entity) = 0;
public:
    SystemBase(ECS *ecs);

    void update();

    void addEntity(EntityID id);
    void removeEntity(EntityID id);

    void markToRemove();
    bool shouldRemove() const;

    std::vector<Bitmask::size_type> getRequiredComponentIds() const;
    std::vector<Bitmask::size_type> getExcludedComponentIds() const;

    bool fits(Bitmask bitmask) const;
};

}
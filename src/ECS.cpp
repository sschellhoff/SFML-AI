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

#include "mercer/ECS/ECS.hpp"

#include "mercer/ECS/Entity.hpp"
#include "mercer/ECS/ComponentBase.hpp"
#include "mercer/ECS/SystemBase.hpp"

namespace mercer {

ECS::ECS() : next_entity_id(0) {
}

Entity ECS::createEntity() {
    return Entity{next_entity_id++, this};
}

void ECS::destroyEntity(EntityID entity_id) {
    components.erase(entity_id);
}

void ECS::registerComponentType(const std::type_info &type) {
    if(component_bitmask_indices.find(type) == component_bitmask_indices.end()) {
        component_bitmask_indices[type] = next_bitmask_index++;
    }
}

void ECS::registerSystem(const SystemBase &system) {
    auto &required_component_types = system.getRequired();
    for(auto &type : required_component_types) {
        registerComponentType(type);
    }
}

void ECS::removeSystem() {
}

}
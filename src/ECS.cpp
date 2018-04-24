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
#include <algorithm>

namespace mercer {

ECS::ECS(Bitmask::size_type max_components) : next_entity_id(0), systemsRequiredComponents(max_components), systemsExcludedComponents(max_components) {
}

void ECS::update() {
    for(auto it = systems.begin(); it != systems.end(); ) {
        if(!(*it)->shouldRemove()) {
            (*it)->update();
            it++;
        } else {
            it = systems.erase(it);
        }
    }
}

Entity ECS::createEntity() {
    bitmasks.insert({next_entity_id++, Bitmask{}});
    return Entity{next_entity_id, this};
}

void ECS::destroyEntity(EntityID entity_id) {
    bitmasks.erase(entity_id);
    components.erase(entity_id);
}

Entity ECS::getEntity(EntityID entity_id) {
    return Entity{entity_id, this};
}

bool ECS::isEntityAlive(EntityID entity_id) {
    return bitmasks.find(entity_id) != bitmasks.end();
}

const Bitmask &ECS::getBitmask(EntityID entity_id) {
    return bitmasks[entity_id];
}

void ECS::registerSystem(SystemBase &system) {
    systems.push_back(&system);
    const auto &requiredComponents = system.getRequiredComponentIds();
    for(auto &component : requiredComponents) {
        systemsRequiredComponents[component].push_back(&system);
    }
    const auto &excludedComponents = system.getExcludedComponentIds();
    for(auto &component : excludedComponents) {
        systemsExcludedComponents[component].push_back(&system);
    }
    addFittingEntitiesToSystem(system);
}

void ECS::removeSystem(SystemBase &system) {
    if(!system.shouldRemove()) {
        system.markToRemove();
    }
    systems.erase(std::remove(systems.begin(), systems.end(), &system), systems.end());
    const auto &requiredComponents = system.getRequiredComponentIds();
    for(auto &component : requiredComponents) {
        auto &req = systemsRequiredComponents[component];
        req.erase(std::remove(req.begin(), req.end(), &system), req.end());
    }
    const auto &excludedComponents = system.getExcludedComponentIds();
    for(auto &component : excludedComponents) {
        auto &exc = systemsExcludedComponents[component];
        exc.erase(std::remove(exc.begin(), exc.end(), &system), exc.end());
    }
}

void ECS::addFittingEntitiesToSystem(SystemBase &system) {
    for(auto &mask : bitmasks) {
        if(system.fits(mask.second)) {
            system.addEntity(mask.first);
        }
    }
}

}
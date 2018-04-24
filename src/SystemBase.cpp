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

#include "mercer/ECS/SystemBase.hpp"
#include "mercer/ECS/Entity.hpp"
#include <algorithm>

namespace mercer {

SystemBase::SystemBase(ECS *ecs) : ecs(ecs), marked_to_remove(false) {
}

void SystemBase::update() {
    for(auto it = entities.begin(); it != entities.end(); ) {
        if(ecs->isEntityAlive(*it) && fits(ecs->getBitmask(*it))) {
            process(ecs->getEntity(*it));
            it++;
        } else {
            it = entities.erase(it);
        }
    }
}

void SystemBase::addEntity(EntityID id) {
    entities.push_back(id);
}

void SystemBase::removeEntity(EntityID id) {
    entities.erase(std::remove(entities.begin(), entities.end(), id), entities.end());
}

void SystemBase::markToRemove() {
    marked_to_remove = true;
    ecs->removeSystem(*this);
}

bool SystemBase::shouldRemove() const {
    return marked_to_remove;
}

std::vector<Bitmask::size_type> SystemBase::getRequiredComponentIds() const {
    return required.getSet();
}

std::vector<Bitmask::size_type> SystemBase::getExcludedComponentIds() const {
    return excluded.getSet();
}

bool SystemBase::fits(Bitmask bitmask) const {
    return bitmask.includes(required) && bitmask.excludes(excluded);
}

}
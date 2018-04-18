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

#include "EntityID.hpp"
#include "ComponentBitmask.hpp"
#include "../Misc/TypeInfoRef.hpp"
#include <unordered_map>
#include <memory>
#include <vector>

namespace mercer {

class Entity;
class SystemBase;
class ComponentBase;

class ECS {
private:
    using ComponentMap = std::unordered_map<Bitmask::size_type, std::unique_ptr<ComponentBase>>;
    using EntitiesComponents = std::unordered_map<EntityID, ComponentMap>;
    using EntitiesBitmask = std::unordered_map<EntityID, Bitmask>;
    using ComponentToSystem = std::vector<std::vector<SystemBase*>>;

    EntityID next_entity_id;

    EntitiesBitmask bitmasks;
    EntitiesComponents components;
    ComponentToSystem systemsRequiredComponents;
    ComponentToSystem systemsExcludedComponents;
    std::vector<SystemBase*> systems;

    void addFittingEntitiesToSystem(SystemBase &system);
public:
    ECS(Bitmask::size_type);

    void update();

    Entity createEntity();
    void destroyEntity(EntityID entity_id);
    Entity getEntity(EntityID entity_id);

    template<typename T>
    T &getComponent(EntityID id) {
        return *static_cast<T*>(components[id][T::GetId()].get());
    }

    template<typename T, typename... Args>
    T &addComponent(EntityID id, Args&&... args) {
        bitmasks[id].set(T::GetId());
        components[id][T::GetId()] = std::make_unique<T>(std::forward<Args>(args)...);
        auto &sysExc = systemsExcludedComponents[T::GetId()];
        for(auto system : sysExc) {
            system->removeEntity(id);
        }
        auto &sysReq = systemsRequiredComponents[T::GetId()];
        for(auto system : sysReq) {
            if(system->fits(bitmasks[id])) {
                system->addEntity(id);
            }
        }
        return getComponent<T>(id);
    }

    template<typename T>
    void removeComponent(EntityID id) {
        bitmasks[id].reset(T::GetId());
        components[id].erase(T::GetId());
        auto &sysExc = systemsExcludedComponents[T::GetId()];
        for(auto system : sysExc) {
            if(system.fits(bitmasks[id])) {
                system->addEntity(id);
            }
        }
        auto &sysReq = systemsRequiredComponents[T::GetId()];
        for(auto system : sysReq) {
            system->removeEntity(id);
        }
    }

    void registerSystem(SystemBase &system);
    void removeSystem(SystemBase &system);
};

}
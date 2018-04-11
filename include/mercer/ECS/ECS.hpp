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

namespace mercer {

class Entity;
class SystemBase;
class ComponentBase;

class ECS {
private:
    using ComponentMap = std::unordered_map<TypeInfoRef, std::unique_ptr<ComponentBase>, Hasher, EqualsTo>;
    using EntityToComponentMap = std::unordered_map<EntityID, ComponentMap>;
    using ComponentToBismaskIndex = std::unordered_map<TypeInfoRef, BitmaskIndexType, Hasher, EqualsTo>;

    EntityID next_entity_id;
    BitmaskIndexType next_bitmask_index;

    EntityToComponentMap components;
    ComponentToBismaskIndex component_bitmask_indices;
public:
    ECS();

    Entity createEntity();
    void destroyEntity(EntityID entity_id);

    template<typename T>
    T &getComponent(EntityID id) {
        return *static_cast<T*>(components[id][typeid(T)].get());
    }

    template<typename T, typename... Args>
    T &addComponent(EntityID id, Args&&... args) {
        components[id][typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
        return getComponent<T>(id);
    }

    template<typename T>
    void removeComponent(EntityID id) {
        components[id].erase(typeid(T));
    }

    template<typename T>
    void registerComponentType() {
        registerComponentType(typeid(T));
    }

    void registerComponentType(const std::type_info &type);

    void registerSystem(const SystemBase &system);
    void removeSystem();
};

}
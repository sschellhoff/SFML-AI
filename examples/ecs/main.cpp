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

#include <string>
#include <iostream>
#include "../../include/mercer/ECS/ECS.hpp"
#include "../../include/mercer/ECS/Entity.hpp"
#include "../../include/mercer/ECS/ComponentBase.hpp"
#include "../../include/mercer/ECS/SystemBase.hpp"

enum ComponentTypes {
    TEXT = 0,
    NUMBER,
    EVIL,
    SIZE
};

class TextComponent : public mercer::ComponentBase {
public:
    static mercer::Bitmask::size_type GetId() {
        return ComponentTypes::TEXT;
    }
    TextComponent(const std::string &text) : text(text) {
    }

    std::string text;
};

class NumberComponent : public mercer::ComponentBase {
public:
    static mercer::Bitmask::size_type GetId() {
        return ComponentTypes::NUMBER;
    }
    NumberComponent() : number(0) {
    }

    NumberComponent(int number) : number(number) {
    }

    int number;
};

class EvilComponent : public mercer::ComponentBase {
public:
    static mercer::Bitmask::size_type GetId() {
        return ComponentTypes::EVIL;
    }
};

class TextSystem : public mercer::SystemBase {
protected:
    virtual void process(mercer::Entity entity) {
        std::cout << entity.getComponent<TextComponent>().text << std::endl;
    }
public:
    TextSystem(mercer::ECS *ecs) : SystemBase(ecs) {
        requires<TextComponent>();
        excludes<EvilComponent>();
    }
};

int main(int argc, char** argv) {
    mercer::ECS ecs{ComponentTypes::SIZE};
    auto entity = ecs.createEntity();
    entity.addComponent<TextComponent>("qwertz");
    auto &number_component = entity.addComponent<NumberComponent>();
    number_component.number = 1337;

    auto entity_bad = ecs.createEntity();
    entity_bad.addComponent<TextComponent>("qwerty");
    entity_bad.addComponent<EvilComponent>();

    TextSystem text_system{&ecs};
    ecs.registerSystem(text_system);

    ecs.update();
}
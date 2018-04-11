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

#include <SFML/Graphics.hpp>
#include <string>
#include "../../include/mercer/ECS/ECS.hpp"
#include "../../include/mercer/ECS/Entity.hpp"
#include "../../include/mercer/ECS/ComponentBase.hpp"
#include "../../include/mercer/ECS/SystemBase.hpp"

class TextComponent : public mercer::ComponentBase {
public:
    TextComponent(const std::string &text) : text(text) {
    }

    std::string text;
};

class NumberComponent : public mercer::ComponentBase {
public:
    NumberComponent() : number(0) {
    }

    NumberComponent(int number) : number(number) {
    }

    int number;
};

class TextSystem : public mercer::SystemBase {
public:
    TextSystem(mercer::ECS *ecs) : SystemBase(ecs) {
        requires<TextComponent>();
    }
};

int main(int argc, char** argv) {

    mercer::ECS ecs;
    auto entity = ecs.createEntity();
    entity.addComponent<TextComponent>("");
    auto &number_component = entity.addComponent<NumberComponent>();
    number_component.number = 1337;

    TextSystem text_system{&ecs};
    ecs.registerSystem(text_system);

    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

    constexpr float TPS = 60;
    const sf::Time time_per_update = sf::seconds(1.0f / TPS);
    unsigned ticks = 0;
    sf::Clock timer;
    auto last_time = sf::Time::Zero;
    auto lag = sf::Time::Zero;

    while(window.isOpen()) {

        auto current_time = timer.getElapsedTime();
        auto elapsed_time = current_time - last_time;
        last_time = current_time;
        lag += elapsed_time;

        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            }
        }

        while(lag >= time_per_update) {
            ticks++;
            lag -= time_per_update;
        }

        window.clear(sf::Color::Black);

        window.display();
    }
}
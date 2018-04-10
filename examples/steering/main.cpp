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

#include "misc.hpp"

int main(int argc, char** argv) {

    const sf::Vector2f agent_position{50.f, 50.f};
    float agent_mass = 1.f;
    float agent_max_speed = 100.f;
    float agent_max_steering_force = 150.f;
    float agent_radius = 20.f;

    const sf::Vector2f target_position{350.f, 250.f};
    const float target_radius = 5.f;

    Vehicle agent {agent_position, agent_mass, agent_max_speed, agent_max_steering_force, agent_radius};

    Target target {target_position, target_radius};

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
            agent.update(target.getPosition(), time_per_update.asSeconds());
        }

        window.clear(sf::Color::Black);

        window.draw(agent);
        window.draw(target);

        window.display();
    }
}
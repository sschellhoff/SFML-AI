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
#include "../../include/mercer/AI/Steering/Seek.hpp"
#include "../../include/mercer/Misc/VectorUtils.hpp"

class Vehicle : public sf::Drawable, public sf::Transformable {
private:
    sf::CircleShape baseShape;
    float mass;
    float max_speed;
    sf::Vector2f target;
    sf::Vector2f velocity;
public:
    Vehicle(const sf::Vector2f &position, const sf::Vector2f &target, float mass, float max_speed, float radius) : baseShape(radius), mass(mass), max_speed(max_speed), target(target), velocity(0.f, 0.f) {
        setPosition(position);
        setOrigin(radius, radius);
        baseShape.setOutlineColor(sf::Color::Green);
        baseShape.setOutlineThickness(3.5f);
        baseShape.setFillColor(sf::Color{100, 5, 133, 255});
    }

    virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const {
        states.transform *= getTransform();
        target.draw(baseShape, states);
    }

    void update(float delta_time) {
        sf::Vector2f acceleration = mercer::seek(target, getPosition(), velocity, max_speed) / mass;
        velocity += acceleration * delta_time;
        velocity = mercer::truncateVector(velocity, max_speed);
        move(velocity * delta_time);
    }
};

int main(int argc, char** argv) {

    sf::Vector2f agent_position{50.f, 50.f};
    float agent_mass = 1.f;
    float agent_max_speed = 100.f;
    float agent_radius = 20.f;

    Vehicle agent {agent_position, sf::Vector2f{350.f, 250.f}, agent_mass, agent_max_speed, agent_radius};

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
            agent.update(time_per_update.asSeconds());
        }

        window.clear(sf::Color::Black);
        window.draw(agent);

        window.display();
    }
}
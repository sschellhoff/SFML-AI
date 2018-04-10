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

#include "misc.hpp"

#include "../../include/mercer/AI/Steering/Seek.hpp"
#include "../../include/mercer/Misc/VectorUtils.hpp"

Vehicle::Vehicle(const sf::Vector2f &position, float mass, float max_speed, float max_steering_force, float radius) : baseShape(radius), mass(mass), max_speed(max_speed), max_steering_force(max_steering_force),velocity(0.f, 0.f), steering_force(0.f, 0.f) {
    setPosition(position);
    setOrigin(radius, radius);
    baseShape.setOutlineColor(sf::Color::Green);
    baseShape.setOutlineThickness(3.5f);
    baseShape.setFillColor(sf::Color{100, 5, 133, 255});
}

void Vehicle::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(baseShape, states);
}

void Vehicle::update(const sf::Vector2f &target, float delta_time) {
    steering_force += mercer::seek(target, getPosition(), velocity, max_speed);
    steering_force = mercer::truncateVector(steering_force, max_steering_force);

    sf::Vector2f acceleration = steering_force / mass;

    velocity += acceleration * delta_time;

    velocity = mercer::truncateVector(velocity, max_speed);

    setPosition(getPosition() + velocity * delta_time);
}

Target::Target(const sf::Vector2f &position, float radius) : baseShape(radius) {
    setPosition(position);
    setOrigin(radius, radius);
    baseShape.setOutlineColor(sf::Color::Blue);
    baseShape.setOutlineThickness(3.5f);
    baseShape.setFillColor(sf::Color{50, 10, 30, 255});
}

void Target::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    states.transform *= getTransform();
    target.draw(baseShape, states);
}
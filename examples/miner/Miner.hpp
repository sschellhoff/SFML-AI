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

#include "../../include/SFMLAI/BaseEntity.hpp"
#include "../../include/SFMLAI/State.hpp"
#include <map>
#include <string>
#include <memory>

enum class MinerStateType;
enum class Location;

class Miner : public BaseEntity {
private:
    int gold_carried;
    const int max_gold;
    int money_in_bank;
    const int comfort_level;
    int thirst;
    const int thirst_level;
    int fatigue;
    const int tiredness_threshold;
    std::string miners_name;
    MinerStateType current_state;
    Location current_location;

    std::map<MinerStateType, std::unique_ptr<State<Miner>>> states;
public:
    Miner(const std::string &name, const int max_gold,
          const int comfort_level, const int thirst_level,
          const int tiredness_threshold);
    Miner(const Miner&) = delete;
    Miner& operator=(const Miner&) = delete;

    virtual void update();
    void changeState(MinerStateType state_type);
    Location currentLocation() const;
    void changeLocation(Location new_location);
    const std::string &name() const;
    void addCarriedGold(int amount);
    void increaseFatigue();
    void decreaseFatigue();
    bool isFatigued() const;
    bool hasFullPockets() const;
    bool isThirsty() const;
    void depositMoney();
    int wealth() const;
    int comfortLevel() const;
    void buyAndDrinkWhiskey();
};
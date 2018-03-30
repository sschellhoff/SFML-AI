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

#include "Miner.hpp"

#include "Locations.hpp"
#include "MinerStates.hpp"

Miner::Miner(const std::string &name, const int max_gold,
             const int comfort_level, const int thirst_level,
             const int tiredness_threshold) :
                gold_carried(0),
                max_gold(max_gold),
                money_in_bank(0),
                comfort_level(comfort_level),
                thirst(0),
                thirst_level(thirst_level),
                fatigue(0),
                tiredness_threshold(tiredness_threshold),
                miners_name(name),
                current_state(MinerStateType::GoHomeSleep),
                current_location(Location::Shack) {

    states[MinerStateType::EnterMineDigNugget] = std::make_unique<EnterMineAndDigForNugget>();
    states[MinerStateType::VisitBankDepositGold] = std::make_unique<VisitBankAndDepositGold>();
    states[MinerStateType::GoHomeSleep] = std::make_unique<GoHomeAndSleepTilRest>();
    states[MinerStateType::QuenchThirst] = std::make_unique<QuenchThirst>();
}

void Miner::update() {
    thirst++;
    states[current_state]->execute(*this);
}

void Miner::changeState(MinerStateType state_type) {
    states[current_state]->exit(*this);
    current_state = state_type;
    states[current_state]->enter(*this);
}

Location Miner::currentLocation() const {
    return current_location;
}

void Miner::changeLocation(Location new_location) {
    current_location = new_location;
}

const std::string &Miner::name() const {
    return miners_name;
}

void Miner::addCarriedGold(int amount) {
    gold_carried += amount;
}

void Miner::increaseFatigue() {
    fatigue++;
}

void Miner::decreaseFatigue() {
    fatigue--;
}

bool Miner::isFatigued() const {
    return fatigue > tiredness_threshold;
}

bool Miner::hasFullPockets() const {
    return gold_carried > max_gold;
}

bool Miner::isThirsty() const {
    return thirst > thirst_level;
}

void Miner::depositMoney() {
    money_in_bank += gold_carried;
    gold_carried = 0;
}

int Miner::wealth() const {
    return money_in_bank;
}

int Miner::comfortLevel() const {
    return comfort_level;
}

void Miner::buyAndDrinkWhiskey() {
    money_in_bank -= 2;
    thirst = 0;
}

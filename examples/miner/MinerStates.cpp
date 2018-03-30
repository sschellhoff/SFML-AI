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

#include "MinerStates.hpp"

#include "Miner.hpp"
#include "Locations.hpp"
#include <iostream>
#include <string>

void switchLocationIfNeeded(Miner &miner, Location location, const std::string &message);
void say(Miner &miner, const std::string &message);

void EnterMineAndDigForNugget::enter(Miner &miner) {
    switchLocationIfNeeded(miner, Location::Goldmine, "Walkin' to the goldmine");
}

void EnterMineAndDigForNugget::execute(Miner &miner) {
    miner.addCarriedGold(1);
    miner.increaseFatigue();

    say(miner, "Pickin' up a nugget");

    if(miner.hasFullPockets()) {
        miner.changeState(MinerStateType::VisitBankDepositGold);
    }

    if(miner.isThirsty()) {
        miner.changeState(MinerStateType::QuenchThirst);
    }
}

void EnterMineAndDigForNugget::exit(Miner &miner) {
    say(miner, "Ah'm leavin' the goldmine with mah pockets full o' sweet gold");
}


void VisitBankAndDepositGold::enter(Miner &miner) {
    switchLocationIfNeeded(miner, Location::Bank, "Goin' to the bank. Yes siree");
}

void VisitBankAndDepositGold::execute(Miner &miner) {
    miner.depositMoney();

    std::cout << miner.name() << ": Depositin' gold. Total savings now: " << miner.wealth() << std::endl;

    if(miner.wealth() >= miner.comfortLevel()) {
        say(miner, "Woohoo! Rich enough for now. Back home to mah li'lle lady");

        miner.changeState(MinerStateType::GoHomeSleep);
    } else {
        miner.changeState(MinerStateType::EnterMineDigNugget);
    }
}

void VisitBankAndDepositGold::exit(Miner &miner) {
    say(miner, "Leavin' the bank");
}


void GoHomeAndSleepTilRest::enter(Miner &miner) {
    switchLocationIfNeeded(miner, Location::Shack, "Walkin' home");
}

void GoHomeAndSleepTilRest::execute(Miner &miner) {
    if(!miner.isFatigued()) {
        say(miner, "What a God darn fantastic nap! Time to find more gold");
        miner.changeState(MinerStateType::EnterMineDigNugget);
    } else {
        miner.decreaseFatigue();
        say(miner, "zZzzZzzzZzzzZZZ...");
    }
}

void GoHomeAndSleepTilRest::exit(Miner &miner) {
    say(miner, "Leavin the house");
}


void QuenchThirst::enter(Miner &miner) {
    switchLocationIfNeeded(miner, Location::Saloon, "Boy, ah sure is thusty! Walkin to the saloon");
}

void QuenchThirst::execute(Miner &miner) {
    if(miner.isThirsty()) {
        miner.buyAndDrinkWhiskey();
        say(miner, "That's mighty fine slippin liquer");

        miner.changeState(MinerStateType::EnterMineDigNugget);
    } else {
        std::cout << "I AM ERROR!" << std::endl;
    }
}

void QuenchThirst::exit(Miner &miner) {
    say(miner, "Leavin' the saloon, feelin' good");
}

void switchLocationIfNeeded(Miner &miner, Location location, const std::string &message) {
    if(miner.currentLocation() != location) {
        say(miner, message),
        miner.changeLocation(location);
    }
}

void say(Miner &miner, const std::string &message) {
    std::cout << miner.name() << ": " << message << std::endl;
}
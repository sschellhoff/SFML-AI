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

#include "../../include/SFMLAI/State.hpp"

enum class MinerStateType {
    EnterMineDigNugget,
    VisitBankDepositGold,
    GoHomeSleep,
    QuenchThirst
};

class Miner;

class EnterMineAndDigForNugget : public State<Miner> {
private:
    EnterMineAndDigForNugget(const EnterMineAndDigForNugget&) = delete;
    EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&) = delete;
public:
    EnterMineAndDigForNugget() {}
    virtual void enter(Miner &miner);
    virtual void execute(Miner &miner);
    virtual void exit(Miner &miner);
};

class VisitBankAndDepositGold : public State<Miner> {
private:
    VisitBankAndDepositGold(const VisitBankAndDepositGold&) = delete;
    VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&) = delete;
public:
    VisitBankAndDepositGold() {}
    virtual void enter(Miner &miner);
    virtual void execute(Miner &miner);
    virtual void exit(Miner &miner);
};

class GoHomeAndSleepTilRest : public State<Miner> {
private:
    GoHomeAndSleepTilRest(const GoHomeAndSleepTilRest&) = delete;
    GoHomeAndSleepTilRest& operator=(const GoHomeAndSleepTilRest&) = delete;
public:
    GoHomeAndSleepTilRest() {}
    virtual void enter(Miner &miner);
    virtual void execute(Miner &miner);
    virtual void exit(Miner &miner);
};

class QuenchThirst : public State<Miner> {
private:
    QuenchThirst(const QuenchThirst&) = delete;
    QuenchThirst& operator=(const QuenchThirst&) = delete;
public:
    QuenchThirst() {}
    virtual void enter(Miner &miner);
    virtual void execute(Miner &miner);
    virtual void exit(Miner &miner);
};
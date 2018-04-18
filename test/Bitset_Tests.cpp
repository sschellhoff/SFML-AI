#include "catch2/catch.hpp"

#include "mercer/Misc/Bitset.hpp"
#include <iostream>

TEST_CASE( "Testing size", "[Bitset]" ) {
    mercer::Bitset<unsigned int> uint_Bitset{3};
    mercer::Bitset<unsigned long> ulong_Bitset(2);
    mercer::Bitset<unsigned long long> ulonglong_Bitset;

    CHECK((8 * sizeof(unsigned int)) == uint_Bitset.getBlockSize());
    CHECK((8 * sizeof(unsigned long)) == ulong_Bitset.getBlockSize());
    CHECK((8 * sizeof(unsigned long long)) == ulonglong_Bitset.getBlockSize());

    CHECK(uint_Bitset.getBlockSize() * 3 == uint_Bitset.size());
    CHECK(ulong_Bitset.getBlockSize() * 2 == ulong_Bitset.size());
    CHECK(ulonglong_Bitset.getBlockSize() == ulonglong_Bitset.size());
}

TEST_CASE( "Testing resize", "[Bitset]" ) {
    mercer::Bitset<unsigned int> uint_Bitset;

    CHECK(1 == uint_Bitset.numBlocks());
    CHECK(uint_Bitset.empty() == false);

    uint_Bitset.resize(0);
    CHECK(0 == uint_Bitset.numBlocks());
    CHECK(uint_Bitset.empty());

    uint_Bitset.resize(7);
    CHECK(7 == uint_Bitset.numBlocks());
    CHECK(uint_Bitset.empty() == false);
}

TEST_CASE("Testing clear", "[Bitset]") {
    mercer::Bitset<> bitset(5);
    
    CHECK(5 == bitset.numBlocks());
    bitset.clear();
    CHECK(0 == bitset.numBlocks());
}

TEST_CASE("Testing push back", "[Bitset]") {
    mercer::Bitset<> bitset;
    bitset.set();
    bitset.push_back(0);
    CHECK(2 == bitset.numBlocks());
    CHECK(bitset.get(bitset.size()-1) == false);
}

TEST_CASE( "Testing accessors", "[Bitset]") {
    mercer::Bitset<> bitset;
    
    CHECK(bitset.none());
    CHECK(bitset.any() == false);
    CHECK(bitset.all() == false);
    bitset.set();
    CHECK(bitset.any());
    CHECK(bitset.all());
    CHECK(bitset.none() == false);
    bitset.reset(1);
    CHECK(bitset.any());
    CHECK(bitset.all() == false);
    CHECK(bitset.none() == false);
    bitset.reset();
    CHECK(bitset.any() == false);
    CHECK(bitset.all() == false);
    CHECK(bitset.none());
    bitset.flip();
    CHECK(bitset.any());
    bitset.flip();
    CHECK(bitset.none());
}

TEST_CASE( "Testing single bit accessors", "[Bitset]") {
    mercer::Bitset<> bitset;

    CHECK(bitset.none());
    bitset.set(2);
    CHECK(bitset.get(2));
    CHECK(bitset.get(1) == false);
    bitset.reset(2);
    CHECK(bitset.get(2) == false);
    CHECK(bitset.none());
    bitset.set();
    CHECK(bitset.all());
    bitset.reset(3);
    CHECK(bitset.get(3) == false);
    CHECK(bitset.get(1));
    bitset.reset();
    CHECK(bitset.none());
    bitset.flip();
    CHECK(bitset.all());
    bitset.reset(3);
    CHECK(bitset.get(3) == false);
    bitset.flip();
    CHECK(bitset.get(3));
    bitset.flip(3);
    CHECK(bitset.get(3) == false);
    CHECK(bitset.get(2) == false);
    bitset.flip(2);
    CHECK(bitset.get(2));
}

TEST_CASE("Testing get first and get next", "[Bitset]") {
    mercer::Bitset<> bitset;
    CHECK(bitset.none());
    CHECK(bitset.size() == bitset.getFirst());
    bitset.set(5);
    std::cout << bitset.toString() << std::endl;
    bitset.set(7);
    std::cout << bitset.toString() << std::endl;
    CHECK(5 == bitset.getFirst());
    CHECK(5 == bitset.getNext(1));
    CHECK(5 == bitset.getNext(5));
    CHECK(7 == bitset.getNext(6));
}

TEST_CASE("Testing includes and excludes", "[Bitset]") {
    mercer::Bitset<> bitset_0{3};
    mercer::Bitset<> bitset_1{3};
    mercer::Bitset<> bitset_2{3};
    mercer::Bitset<> bitset_3{3};
    mercer::Bitset<> bitset_4{3};
    
    bitset_0.set(1);
    bitset_0.set(7);
    bitset_0.set(29);
    bitset_0.set(33);
    bitset_0.set(64);
    bitset_0.set(71);
    bitset_0.set(72);

    bitset_1.set(1);
    bitset_1.set(7);
    bitset_1.set(29);
    bitset_1.set(33);
    bitset_1.set(64);
    bitset_1.set(71);
    bitset_1.set(72);

    bitset_2.set(7);
    bitset_2.set(29);
    bitset_2.set(64);
    bitset_2.set(72);

    bitset_3.set(71);

    bitset_4.set(4);
    bitset_4.set(22);
    bitset_4.set(40);
    bitset_4.set(70);
    
    CHECK(bitset_0.includes(bitset_1));
    CHECK(bitset_0.includes(bitset_2));
    CHECK(bitset_0.includes(bitset_3));
    CHECK(bitset_0.includes(bitset_4) == false);
    CHECK(bitset_3.includes(bitset_0) == false);
    CHECK(bitset_4.includes(bitset_0) == false);

    CHECK(bitset_0.excludes(bitset_1) == false);
    CHECK(bitset_0.excludes(bitset_2) == false);
    CHECK(bitset_0.excludes(bitset_3) == false);
    CHECK(bitset_0.excludes(bitset_4));
}

TEST_CASE("Testing getting set", "[Bitset]") {
    mercer::Bitset<> bitset{3};

    bitset.set(0);
    auto set = bitset.getSet();
    CHECK((set.size() == 1 && set[0] == 0));

    bitset.set(33);
    set = bitset.getSet();
    CHECK((set.size() == 2 && set[0] == 0 && set[1] == 33));
}

TEST_CASE("Testing to string", "[Bitset]") {
    mercer::Bitset<> bitset;
    bitset.set(1);
    bitset.set(3);
    CHECK(std::string("01010000000000000000000000000000") == bitset.toString());
}

// more tests for:
// operators
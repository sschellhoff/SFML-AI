#include "catch2/catch.hpp"

#include "mercer/Misc/Bitset.hpp"


TEST_CASE( "Testing size", "[Bitset]" ) {
    mercer::Bitset<unsigned int> uint_Bitset{3};
    mercer::Bitset<unsigned long> ulong_Bitset(2);
    mercer::Bitset<unsigned long long> ulonglong_Bitset;

    CHECK(sizeof(unsigned int) == uint_Bitset.getBlockSize());
    CHECK(sizeof(unsigned long) == ulong_Bitset.getBlockSize());
    CHECK(sizeof(unsigned long long) == ulonglong_Bitset.getBlockSize());

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
}

// more tests for:
// set
// reset
// flip
// get
// clear
// push back
// getFirst
// getNext
// toString
// operators
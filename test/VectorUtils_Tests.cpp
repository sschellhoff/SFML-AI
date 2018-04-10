#include "catch2/catch.hpp"

#include "mercer/Misc/VectorUtils.hpp"

bool equals(const sf::Vector2f &a, const sf::Vector2f &b);
bool equals(float a, float b);

// float vectorLengthSquared(const sf::Vector2f &vector)
TEST_CASE( "Testing vectorLengthSquared", "[VectorUtils][vectorLengthSquared]" ) {
    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{0, 0}), 0) );

    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{0, 1}), 1) );
    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{1, 0}), 1) );

    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{1, 1}), 2) );

    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{2, 1}), 5) );
    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{2, 4}), 20) );

    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{-1, 0}), 1) );
    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{0, -1}), 1) );

    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{-2, -3}), 13) );

    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{-7, 3}), 58) );

    CHECK( equals(mercer::vectorLengthSquared(sf::Vector2f{5, -9}), 106) );
}

// float vectorLength(const sf::Vector2f &vector)
TEST_CASE( "Testing vectorLength", "[VectorUtils][vectorLength]" ) {
    CHECK( equals(mercer::vectorLength(sf::Vector2f{0, 0}), 0) );

    CHECK( equals(mercer::vectorLength(sf::Vector2f{0, 1}), 1) );
    CHECK( equals(mercer::vectorLength(sf::Vector2f{1, 0}), 1) );

    CHECK( equals(mercer::vectorLength(sf::Vector2f{1, 1}), 1.41421356237f) );

    CHECK( equals(mercer::vectorLength(sf::Vector2f{2, 1}), 2.2360679775f) );
    CHECK( equals(mercer::vectorLength(sf::Vector2f{2, 4}), 4.472135955f) );

    CHECK( equals(mercer::vectorLength(sf::Vector2f{-1, 0}), 1) );
    CHECK( equals(mercer::vectorLength(sf::Vector2f{0, -1}), 1) );

    CHECK( equals(mercer::vectorLength(sf::Vector2f{-2, -3}), 3.60555127546f) );

    CHECK( equals(mercer::vectorLength(sf::Vector2f{-7, 3}), 7.61577310586f) );

    CHECK( equals(mercer::vectorLength(sf::Vector2f{5, -9}), 10.295630141f) );
}

// sf::Vector2f processDeadzone(sf::Vector2f vector, float deadzone)
TEST_CASE( "Testing processDeadzone", "[VectorUtils][processDeadzone]" ) {
    //CHECK ( true == false ); // write tests
}

// sf::Vector2f getNormalized(const sf::Vector2f &vector)
TEST_CASE( "Testing getNormalized", "[VectorUtils][getNormalized]" ) {
    CHECK( equals(mercer::getNormalized(sf::Vector2f{0, 0}), sf::Vector2f{0, 0}) );

    CHECK( equals(mercer::getNormalized(sf::Vector2f{0, 1}), sf::Vector2f{0, 1}) );
    CHECK( equals(mercer::getNormalized(sf::Vector2f{1, 0}), sf::Vector2f{1, 0}) );

    CHECK( equals(mercer::getNormalized(sf::Vector2f{1, 1}), sf::Vector2f{0.70710678118f, 0.70710678118f}) );

    CHECK( equals(mercer::getNormalized(sf::Vector2f{0, -1}), sf::Vector2f{0, -1}) );
    CHECK( equals(mercer::getNormalized(sf::Vector2f{-1, 0}), sf::Vector2f{-1, 0}) );

    CHECK( equals(mercer::getNormalized(sf::Vector2f{-2, -3}), sf::Vector2f{-0.55470019622f, -0.83205029433f}) );

    CHECK( equals(mercer::getNormalized(sf::Vector2f{-7, 3}), sf::Vector2f{-0.91914503001f, 0.39391929857f}) );
    CHECK( equals(mercer::getNormalized(sf::Vector2f{5, -9}), sf::Vector2f{0.48564293117f, -0.87415727612f}) );
}

// sf::Vector2f truncateVector(const sf::Vector2f &vector, float length)
TEST_CASE( "Testing truncateVector", "[VectorUtils][truncateVector]" ) {
    //CHECK ( true == false ); // write tests
}

bool equals(const sf::Vector2f &a, const sf::Vector2f &b) {
    return equals(a.x, b.x) && equals(a.y, b.y);
}

bool equals(float a, float b) {
    return a == Approx(b);
}
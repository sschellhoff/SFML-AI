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
    const sf::Vector2f zero{0, 0};
    const sf::Vector2f one{1, 1};
    const sf::Vector2f one_m{-1, -1};
    const sf::Vector2f x_axis{1, 0};
    const sf::Vector2f x_axis_neg{-1, 0};
    const sf::Vector2f y_axis{0, 1};
    const sf::Vector2f y_axis_neg{0, -1};
    CHECK( equals(mercer::processDeadzone(zero, 0), zero) );

    CHECK( equals(mercer::processDeadzone(one, 0), one) );
    CHECK( equals(mercer::processDeadzone(one_m, 0), one_m) );
    CHECK( equals(mercer::processDeadzone(x_axis, 0), x_axis) );
    CHECK( equals(mercer::processDeadzone(x_axis_neg, 0), x_axis_neg) );
    CHECK( equals(mercer::processDeadzone(y_axis, 0), y_axis) );
    CHECK( equals(mercer::processDeadzone(y_axis_neg, 0), y_axis_neg) );

    CHECK( equals(mercer::processDeadzone(one, 1.5f), zero) );
    CHECK( equals(mercer::processDeadzone(one_m, 1.5f), zero) );
    CHECK( equals(mercer::processDeadzone(x_axis, 1.5f), zero) );
    CHECK( equals(mercer::processDeadzone(x_axis_neg, 1.5f), zero) );
    CHECK( equals(mercer::processDeadzone(y_axis, 1.5f), zero) );
    CHECK( equals(mercer::processDeadzone(y_axis_neg, 1.5f), zero) );
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
    const sf::Vector2f zero{0, 0};
    const sf::Vector2f one{1, 1};
    const sf::Vector2f one_m{-1, -1};
    const sf::Vector2f x_axis{1, 0};
    const sf::Vector2f x_axis_neg{-1, 0};
    const sf::Vector2f y_axis{0, 1};
    const sf::Vector2f y_axis_neg{0, -1};
    CHECK( equals(mercer::truncateVector(zero, 0.f), zero) );
    CHECK( equals(mercer::truncateVector(zero, 2.f), zero) );

    CHECK( equals(mercer::truncateVector(x_axis, 2.f), sf::Vector2f{2, 0}) );
    CHECK( equals(mercer::truncateVector(x_axis_neg, 2.f), sf::Vector2f{-2, 0}) );
    CHECK( equals(mercer::truncateVector(y_axis, 2.f), sf::Vector2f{0, 2}) );
    CHECK( equals(mercer::truncateVector(y_axis_neg, 2.f), sf::Vector2f{0, -2}) );

    CHECK( equals(mercer::truncateVector(one, 5.f), sf::Vector2f(3.53553390594f, 3.53553390594f)) );
    CHECK( equals(mercer::truncateVector(one_m, 5.f), sf::Vector2f(-3.53553390594f, -3.53553390594f)) );
}

// Helper Methods

bool equals(const sf::Vector2f &a, const sf::Vector2f &b) {
    return equals(a.x, b.x) && equals(a.y, b.y);
}

bool equals(float a, float b) {
    return a == Approx(b);
}
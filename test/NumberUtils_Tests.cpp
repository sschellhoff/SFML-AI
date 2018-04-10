#include "catch2/catch.hpp"

#include "mercer/Misc/NumberUtils.hpp"

// T clamp(T value, T min, T max)
TEST_CASE( "Testing clamp", "[NumberUtils][clamp]" ) {
    // value = min = max
    CHECK( mercer::clamp(0, 0, 0) == 0 );

    // value > min = max
    CHECK( mercer::clamp(1, 0, 0) == 0 );

    // value = max
    CHECK( mercer::clamp(1, 0, 1) == 1 );

    // value = min
    CHECK( mercer::clamp(0, 0, 1) == 0 );

    // value < min
    CHECK( mercer::clamp(-1, 0, 1) == 0 );

    // value > max
    CHECK( mercer::clamp(2, 0, 1) == 1 );

    // min > max, value between
    CHECK( mercer::clamp(1, 2, 0) == 2 );

    // min > max, value smaller
    CHECK( mercer::clamp(-1, 2, 0) == 2 );

    // min > max, value greater
    CHECK( mercer::clamp(3, 2, 0) == 0 );
}

// T thresholdCutoff(T value, T min_threshold, T max_threshold, T null_value)
TEST_CASE( "Testing thresholdCutoff", "[NumberUtils][thresholdCutoff]" ) {
    CHECK( mercer::thresholdCutoff(0, 0, 0, 0) == 0 );
    CHECK( mercer::thresholdCutoff(-1, 0, 0, 0) == -1 );
    CHECK( mercer::thresholdCutoff(1, 0, 0, 0) == 1 );

    CHECK( mercer::thresholdCutoff(0, 0, 1, 0) == 0 );
    CHECK( mercer::thresholdCutoff(1, 0, 1, 0) == 1 );

    CHECK( mercer::thresholdCutoff(1, 0, 2, 0) == 0 );

    CHECK( mercer::thresholdCutoff(1, 0, 2, 5) == 5 );
}
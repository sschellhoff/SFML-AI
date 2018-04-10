cmake_minimum_required(VERSION 2.8)
project(tate_engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include_directories(
)

link_directories(
    /usr/local/lib
)

add_executable(
    tests
    main.cpp
    NumberUtils_Tests.cpp
    VectorUtils_Tests.cpp
)

target_link_libraries(
    tests
    -lmercer
)
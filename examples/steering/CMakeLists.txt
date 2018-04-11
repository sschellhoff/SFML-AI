cmake_minimum_required(VERSION 2.8)
project(tate_engine)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(
)

link_directories(
    /usr/local/lib
)

add_executable(
    steering
    main.cpp
    misc.cpp
    ../../src/Arrive.cpp
    ../../src/VectorUtils.cpp
)

target_link_libraries(
    steering
    -lsfml-audio
    -lsfml-graphics
    -lsfml-network
    -lsfml-window
    -lsfml-system
)
               
install(TARGETS steering RUNTIME DESTINATION bin)
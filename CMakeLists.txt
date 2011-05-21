# One Astronaut: CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(one_astronaut C)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH}
    "${CMAKE_SOURCE_DIR}/cmake/")

find_package(Allegro REQUIRED)

include_directories(${ALLEGRO_INCLUDE_DIRS})

add_executable(one_astronaut
    main.c
    one_astronaut.c
    events.c
    update.c
    draw.c
)

target_link_libraries(one_astronaut
    ${ALLEGRO_LIBRARIES}
)


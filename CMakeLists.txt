# One Astronaut: CMakeLists.txt

cmake_minimum_required(VERSION 2.6)

project(one_astronaut C)

if(WIN32)
    set(ALLEGRO_INCLUDE_DIR ${CMAKE_BINARY_DIR}/${ALLEGRO_PATH}/include)
    set(ALLEGRO_LIB_DIR ${CMAKE_BINARY_DIR}/${ALLEGRO_PATH}/bin)
    set(ALLEGRO_LIB
        allegro-5.0.2-mt
    )
endif(WIN32)

link_directories(${ALLEGRO_LIB_DIR})
include_directories(${ALLEGRO_INCLUDE_DIR})

add_executable(one_astronaut
    main.c
    one_astronaut.c
)

target_link_libraries(one_astronaut
    ${ALLEGRO_LIB}
)


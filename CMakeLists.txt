
cmake_minimum_required(VERSION 2.8)

project(lifeGame)
include_directories(world_maps)
include_directories(saved_worlds)
#adding needed files
file(COPY world_maps/default_world.txt DESTINATION world_maps)
file(COPY world_maps/another_world.txt DESTINATION world_maps)
file(COPY world_maps/xd_world.txt DESTINATION world_maps)
file(COPY world_maps/one_more_world.txt DESTINATION world_maps)
file(COPY saved_worlds/default_saved.txt DESTINATION saved_worlds)


set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")

#change this to Release to activate optimization and compile without debug symbols
set(CMAKE_BUILD_TYPE Debug)

#adds arbitrary flags to the compiler.
#this one is used to generate the files we give in input to Egypt.
set(CMAKE_C_FLAGS "-std=c99 -fdump-rtl-expand")

#linking SDL2
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${SDL2_IMAGE_INCLUDE_DIRS})

add_executable(lifeGame main.c config.c logic.c graph.c saved_worlds world_maps)
target_link_libraries(lifeGame ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES})

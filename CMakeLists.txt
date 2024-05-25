cmake_minimum_required(VERSION 3.25)
project(helloSDL C)

# use dynamic SDL2 libraries only
set(SDL2_USE_STATIC_LIBS OFF)
# ensure that SDL2 package is available
find_package(SDL2)
# includes all SDL2 includes directories
include_directories(${SDL2_INCLUDE_DIR})

set(CMAKE_C_STANDARD 11)

add_executable(helloSDL main.c)

#Then, SDL2 libraries are linked ($SDL2_LIBRARIES Means -lSDL2)
target_link_libraries(helloSDL ${SDL2_LIBRARIES})

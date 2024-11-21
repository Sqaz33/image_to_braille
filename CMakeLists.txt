cmake_minimum_required(FATAL_ERROR VERSION 3.5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

project(image_to_braille)

find_package(OpenCV CONFIG REQUIRED)

file(GLOB_RECURSE SRC "src/*.cpp")
file(GLOB_RECURSE INCLUDE "include/*.hpp")

add_executable(img2Braille ${SRC} ${INCLUDE})

target_link_libraries(img2Braille PRIVATE ${OpenCV_LIBS})


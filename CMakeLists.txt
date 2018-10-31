
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_library(pixel STATIC 
  pixel/src/Window.cpp
  pixel/src/Canvas.cpp
)
target_include_directories(pixel PUBLIC pixel/include)
target_link_libraries(pixel PUBLIC GLEW::GLEW OpenGL::GL SDL2)

add_executable(image_swap examples/image_swap/src/image_swap.cpp)
target_link_libraries(image_swap PRIVATE pixel)
add_executable(randomdots examples/randomdots/src/randomdots.cpp)
target_link_libraries(randomdots PRIVATE pixel)
add_executable(conway examples/conway/src/conway.cpp)
target_link_libraries(conway PRIVATE pixel)
add_executable(colors examples/colors/src/colors.cpp)
target_link_libraries(colors PRIVATE pixel)
add_executable(mousetrail examples/mousetrail/src/mousetrail.cpp)
target_link_libraries(mousetrail PRIVATE pixel)




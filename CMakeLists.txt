
cmake_minimum_required(VERSION 3.0)
set(CMAKE_CXX_STANDARD 17)

project(
  pixel
  VERSION 0.1
  )


set(CMAKE_DEBUG_POSTFIX d)

set(OpenGL_GL_PREFERENCE "LEGACY")
find_package(GLEW REQUIRED)
find_package(OpenGL REQUIRED)
find_package(SDL2 REQUIRED)

add_library(pixel STATIC
  pixel/src/Window.cpp
  pixel/src/Canvas.cpp
)

target_include_directories(
  pixel
  PUBLIC
  $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/pixel/include>
  $<INSTALL_INTERFACE:include>
  )
target_link_libraries(pixel PUBLIC GLEW::GLEW OpenGL::GL)

if(NOT TARGET SDL2::SDL2)
  target_link_libraries(pixel PUBLIC SDL2)
else()
  target_link_libraries(pixel PUBLIC SDL2::SDL2)
endif()

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
add_executable(platformer examples/platformer/src/platformer.cpp)
target_link_libraries(platformer PRIVATE pixel)
add_executable(simple examples/simple/src/simple.cpp)
target_link_libraries(simple PRIVATE pixel)
add_executable(starfield examples/starfield/src/starfield.cpp)
target_link_libraries(starfield PRIVATE pixel)


# Install Section
include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  ${PROJECT_BINARY_DIR}/pixelConfigVersion.cmake
  VERSION ${PROJECT_VERSION}
  COMPATIBILITY SameMajorVersion
  )

configure_package_config_file(
  pixelConfig.cmake.in
  ${PROJECT_BINARY_DIR}/pixelConfig.cmake
  INSTALL_DESTINATION ${CMAKE_INSTALL_DATADIR}/pixel
  )

install(
  TARGETS pixel
  EXPORT pixelTarget
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  )

install(
  EXPORT pixelTarget
  FILE  pixelTarget.cmake
  NAMESPACE pixel::
  DESTINATION ${CMAKE_INSTALL_DATADIR}/pixel
  )

install(
  DIRECTORY pixel/include
  DESTINATION  ${CMAKE_INSTALL_PREFIX}
  )

install(
  FILES
  ${PROJECT_SOURCE_DIR}/LICENSE
  DESTINATION  ${CMAKE_INSTALL_DATADIR}/pixel/copyright
  )

install(
  FILES
  ${PROJECT_BINARY_DIR}/pixelConfig.cmake
  ${PROJECT_BINARY_DIR}/pixelConfigVersion.cmake
  DESTINATION ${CMAKE_INSTALL_DATADIR}/pixel
  )

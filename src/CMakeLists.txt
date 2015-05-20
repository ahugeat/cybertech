cmake_minimum_required(VERSION 2.8)

project(CyberTech CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)

add_definitions(-Wall -g -O2 -std=c++11)

add_executable(cybertech
    demo.cc
)

target_link_libraries(cybertech
  ${SFML2_LIBRARIES}
)

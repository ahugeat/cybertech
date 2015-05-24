cmake_minimum_required(VERSION 2.8)

project(CyberTech CXX)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SFML2 REQUIRED sfml-graphics>=2.1 sfml-audio>=2.1)

set(CMAKE_MODULE_PATH
  ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/../modules")

find_package(Box2D REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)

add_definitions(-Wall -g -O2 -std=c++11)

add_executable(cybertech
	demo.cc
	game/Assets.cc
	game/Entity.cc
	game/Group.cc
	game/Random.cc
	game/Resources.cc
	local/Bones.cc
	local/Hero.cc
	local/Platforms.cc
	local/SFMLDebugDraw.cc
)

target_link_libraries(cybertech
	${SFML2_LIBRARIES}
	${BOX2D_LIBRARIES}
	${Boost_LIBRARIES}
)

cmake_minimum_required(VERSION 3.10.0)
project(snek VERSION 0.1.0 LANGUAGES C CXX)

add_executable(snek 
	src/main.cpp
	src/app.cpp
	src/snake.cpp
	src/io.cpp
	src/food.cpp
)

target_include_directories(snek PRIVATE
	${PROJECT_SOURCE_DIR}/incl
)

set_target_properties(snek PROPERTIES
	RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin
)

target_compile_options(snek PRIVATE 
	-O3 -Wall -Wextra -Wpedantic
)

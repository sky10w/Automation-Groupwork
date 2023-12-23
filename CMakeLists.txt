cmake_minimum_required(VERSION 3.20)

project(
    Automation_Experiment
    LANGUAGES CXX
    DESCRIPTION "automation experiment"
    VERSION 0.2
)

aux_source_directory(. SRC)
# set(SRC ./test.cpp)
# set(CMAKE_GENERATOR "MinGW Makefile")

add_subdirectory(basic_types)

message(${SRC})
add_executable(main ${SRC})
target_include_directories(main PRIVATE .)
target_link_libraries(main PRIVATE basic_types)
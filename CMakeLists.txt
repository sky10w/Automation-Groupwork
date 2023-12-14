cmake_minimum_required(VERSION 3.20)

project(
    Automation_Experiment
    LANGUAGES CXX
    DESCRIPTION "automation experiment"
    VERSION 0.2
)


aux_source_directory(. SRC)
add_subdirectory(basic_types)

add_executable(main ${SRC})
target_include_directories(main PRIVATE)
target_compile_features(main PRIVATE cxx_std_20)
target_link_libraries(main basic_types)
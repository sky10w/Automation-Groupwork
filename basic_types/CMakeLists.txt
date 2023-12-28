cmake_minimum_required(VERSION 3.20)

project(
    basic_types
    LANGUAGES CXX
    DESCRIPTION "automation experiment"
    VERSION 0.2
)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(EXPORT_COMPILE_COMMANDS ON)

aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR} SRC_SUB)
set(HEADER_SUB macros.hpp Edge.hpp Map.hpp Node.hpp Edge_imp.hpp RG.hpp)
message(${SRC_SUB})

add_library(basic_types STATIC ${SRC_SUB} ${HEADER_SUB})

target_compile_options(basic_types PRIVATE -Wall)
target_include_directories(basic_types PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
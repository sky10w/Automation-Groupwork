cmake_minimum_required(VERSION 3.20)

project(
    basic_types
    LANGUAGES CXX
    DESCRIPTION "automation experiment"
    VERSION 0.2
)

set(WINDOWS_EXPORT_ALL_SYMBOLS ON)

aux_source_directory(. SRC_SUB)

add_library(basic_types ${SRC_SUB})
target_include_directories(basic_types PUBLIC .)
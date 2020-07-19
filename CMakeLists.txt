cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)


project(json-cpp
        VERSION 2019.1.0
        DESCRIPTION "Json c++ library"
        LANGUAGES CXX)

SET(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")

set (json_cpp_files
        src/json_cpp.cpp
        src/json_base.cpp
        src/json_util.cpp
        src/json_builder.cpp
        src/json_object.cpp
        )

add_library(json-cpp ${json_cpp_files})

set_target_properties(json-cpp
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED On
        CXX_EXTENSIONS Off
        VERSION ${PROJECT_VERSION})

if(MSVC)
    target_compile_options(json-cpp PRIVATE /W4)
else(MSVC)
    target_compile_options(json-cpp PRIVATE -Wall -Wextra -pedantic)
endif(MSVC)

target_include_directories(json-cpp
        SYSTEM INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_include_directories(json-cpp
        PRIVATE
        include )

export(TARGETS json-cpp FILE JsonCppConfig.cmake)

###
### TESTS
###
find_package(CatchTests CONFIG QUIET)

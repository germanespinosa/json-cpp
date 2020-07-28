cmake_minimum_required(VERSION 3.13)

set(CMAKE_CXX_STANDARD 17)

project(json-cpp
        VERSION 2019.1.0
        DESCRIPTION "Json c++ library"
        LANGUAGES CXX)

find_package(CURL REQUIRED)

message("HERE2 ${CURL_LIBRARIES}")

set (json_cpp_files
        src/json_cpp.cpp
        src/json_base.cpp
        src/json_util.cpp
        src/json_builder.cpp
        src/json_object.cpp
        )

add_library(json-cpp ${json_cpp_files})

target_link_libraries(json-cpp
        PUBLIC
        ${CURL_LIBRARIES})

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

include(GNUInstallDirs)

install(TARGETS json-cpp EXPORT Json-cppConfig
        ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT Json-cppConfig
        DESTINATION ${CMAKE_INSTALL_DATADIR}/cmake/Json-cpp
        EXPORT_LINK_INTERFACE_LIBRARIES)

export(TARGETS json-cpp FILE Json-cppConfig.cmake)

install(CODE "FILE(APPEND ${CMAKE_INSTALL_FULL_DATADIR}/cmake/Json-cpp/Json-cppConfig.cmake \"find_package(CURL
REQUIRED)\n\") ")
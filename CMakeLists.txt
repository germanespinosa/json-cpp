cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(json-cpp
        VERSION 2019.1.0
        DESCRIPTION "Json c++ library"
        LANGUAGES CXX)

####
#### DEPENDENCIES
####

#if (NOT EXISTS ${CMAKE_CURRENT_BINARY_DIR}/DependenciesConfig.cmake)
#    file(DOWNLOAD https://raw.githubusercontent.com/germanespinosa/dependencies/main/DependenciesConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/DependenciesConfig.cmake)
#endif()
#set(Dependencies_DIR "${CMAKE_CURRENT_BINARY_DIR}")
find_package (Dependencies REQUIRED)

install_git_dependency(
        https://github.com/HowardHinnant/date
        PUBLIC
        INCLUDE_DIRECTORIES
            include )

dependency_include(include)

set (json_cpp_files
        src/json_cpp.cpp
        src/json_base.cpp
        src/json_date.cpp
        src/json_buffer.cpp
        src/json_base64.cpp
        src/json_util.cpp
        src/json_builder.cpp
        src/json_object.cpp
        src/json_dictionary.cpp
        )

add_library(json-cpp ${json_cpp_files})


set_target_properties(json-cpp
        PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED On
        CXX_EXTENSIONS Off
        VERSION ${PROJECT_VERSION})

target_include_directories(json-cpp
        SYSTEM INTERFACE
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>)

target_include_directories(json-cpp
        PRIVATE
        include)

target_compile_options(json-cpp PRIVATE -Wextra -pedantic -Wall -fPIC)

###
### TESTS
###

install_dependency(https://github.com/germanespinosa/catch
        PACKAGES
        CatchTests
        PUBLIC)

test_library(json-cpp)

###
### LIBRARY INSTALLATION
###

export(TARGETS json-cpp FILE JsonCppConfig.cmake)

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
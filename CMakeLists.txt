cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)

project(json-cpp
        VERSION 2019.1.0
        DESCRIPTION "Json c++ library"
        LANGUAGES CXX)

find_package(CURL REQUIRED)

### download and install dependency library
FILE(DOWNLOAD
        https://raw.githubusercontent.com/germanespinosa/dependencies/main/dependencies.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/dependencies.cmake)

include(${CMAKE_CURRENT_BINARY_DIR}/dependencies.cmake)
###

install_dependency(https://github.com/HowardHinnant/date)

dependency_include(dependencies/date/include include)

set (json_cpp_files
        src/json_cpp.cpp
        src/json_base.cpp
        src/json_date.cpp
        src/json_buffer.cpp
        src/json_base64.cpp
        src/json_util.cpp
        src/json_builder.cpp
        src/json_object.cpp
        src/json_web_request.cpp
        src/json_web_response.cpp
        src/json_dictionary.cpp
        )

add_library(json-cpp ${json_cpp_files})

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")

target_link_libraries(json-cpp
        PUBLIC
        ${CURL_LIBRARIES})

set_target_properties(json-cpp
        PROPERTIES
        CXX_STANDARD 20
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
        include)

###
### TESTS
###

install_dependency(https://github.com/germanespinosa/catch CatchTests)
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

install(CODE "FILE(APPEND ${CMAKE_INSTALL_FULL_DATADIR}/cmake/Json-cpp/Json-cppConfig.cmake \"find_package(CURL REQUIRED)\n\") ")
install(CODE "FILE(APPEND ${CMAKE_INSTALL_FULL_DATADIR}/cmake/Cellworld/CellworldConfig.cmake \"set(JSON-CPP_LIBRARIES json-cpp ${CURL_LIBRARIES})\n\") ")

cmake_minimum_required(VERSION 2.6)
project("Charlotte2D")

FILE(GLOB src
    "source/*.cpp"
)
add_library(charlotte STATIC "${src}")
target_include_directories(charlotte PUBLIC
    "source"
)

# External libs
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(SFML 2 REQUIRED network audio graphics window system)
if (SFML_FOUND)
    include_directories(${SFML_INCLUDE_DIR})
    target_link_libraries(charlotte ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

# Examples
option(BUILD_EXAMPLES "Build examples" true)
if (BUILD_EXAMPLES)
    add_subdirectory("example")
endif()

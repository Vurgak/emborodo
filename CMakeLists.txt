cmake_minimum_required(VERSION 3.28.3)
project(emborodo)

option(BUILD_SHARED_LIBS "Tell add_library() to default to SHARED libraries, instead of STATIC libraries, when called with no explicit library type." ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/CPM.cmake)
CPMAddPackage("gh:catchorg/Catch2@3.8.0")
CPMAddPackage("gh:boostorg/pfr#2.2.0")
CPMAddPackage("gh:Neargye/magic_enum#v0.9.7")
CPMAddPackage("gh:marzer/tomlplusplus@3.4.0")
CPMAddPackage("gh:tinyobjloader/tinyobjloader@1.0.6")

include(FetchContent)
include(cmake/Glfw.cmake)
include(cmake/Glm.cmake)
include(cmake/ImGui.cmake)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb)

enable_testing()

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ASSETS_PATH "${CMAKE_SOURCE_DIR}/assets/")
else()
    set(ASSETS_PATH "./")
endif()

add_subdirectory(sources/enborodo)
add_subdirectory(sources/emborodo)

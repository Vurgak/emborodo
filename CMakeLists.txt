cmake_minimum_required(VERSION 3.28.3)
project(emborodo)

option(BUILD_SHARED_LIBS "Build the library as a shared library" ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
include(cmake/Glfw.cmake)

file(GLOB_RECURSE ENBORODO_SOURCES CONFIGURE_DEPENDS sources/enborodo/*.cpp sources/enborodo/*.hpp)
add_library(enborodo)
target_sources(enborodo PRIVATE ${ENBORODO_SOURCES})
target_include_directories(enborodo PUBLIC sources)
target_link_libraries(enborodo PUBLIC glfw)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(enborodo PRIVATE EN_SHARED)
    set_target_properties(enborodo PROPERTIES DEFINE_SYMBOL EN_EXPORTS)
endif()

if(MSVC)
    target_compile_options(enborodo PRIVATE /W4)
else()
    target_compile_options(enborodo PRIVATE -Wall -Wextra -Wpedantic)
endif()

file(GLOB_RECURSE EMBORODO_SOURCES CONFIGURE_DEPENDS sources/emborodo/*.cpp sources/emborodo/*.hpp)
add_executable(emborodo)
target_sources(emborodo PRIVATE ${EMBORODO_SOURCES})
target_include_directories(emborodo PRIVATE sources)
target_link_libraries(emborodo PUBLIC enborodo)

if(MSVC)
    target_compile_options(emborodo PRIVATE /W4)
else()
    target_compile_options(emborodo PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_command(
        TARGET emborodo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:emborodo> $<TARGET_RUNTIME_DLLS:emborodo>
        COMMAND_EXPAND_LISTS)

cmake_minimum_required(VERSION 3.28.3)
project(emborodo)

option(BUILD_SHARED_LIBS "Tell add_library() to default to SHARED libraries, instead of STATIC libraries, when called with no explicit library type." ON)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

include(cmake/CPM.cmake)
CPMAddPackage("gh:Neargye/magic_enum#v0.9.7")
CPMAddPackage(
        NAME assimp
        GITHUB_REPOSITORY assimp/assimp
        VERSION 5.4.3
        OPTIONS "ASSIMP_BUILD_TESTS OFF" "ASSIMP_INSTALL OFF")

include(FetchContent)
include(cmake/Glfw.cmake)
include(cmake/Glm.cmake)
include(cmake/ImGui.cmake)

add_subdirectory(vendor/glad)
add_subdirectory(vendor/stb)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(ASSETS_PATH ${CMAKE_SOURCE_DIR}/assets/)
else()
    set(ASSETS_PATH ./assets/)
endif()

file(GLOB_RECURSE ENBORODO_SOURCES CONFIGURE_DEPENDS sources/enborodo/*.cpp sources/enborodo/*.hpp)
add_library(enborodo)
target_sources(enborodo PRIVATE ${ENBORODO_SOURCES})
target_include_directories(enborodo PUBLIC sources)
target_link_libraries(enborodo PUBLIC assimp glad glfw glm::glm imgui magic_enum::magic_enum stb)

if (BUILD_SHARED_LIBS)
    target_compile_definitions(enborodo PRIVATE EN_SHARED)
    set_target_properties(enborodo PROPERTIES DEFINE_SYMBOL EN_EXPORTS)
endif()

if (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    target_link_libraries(enborodo PUBLIC winmm)
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
target_link_libraries(emborodo PRIVATE enborodo)
target_compile_definitions(emborodo PRIVATE EM_ASSETS_PATH="${ASSETS_PATH}")

if(MSVC)
    target_compile_options(emborodo PRIVATE /W4)
else()
    target_compile_options(emborodo PRIVATE -Wall -Wextra -Wpedantic)
endif()

add_custom_command(
        TARGET emborodo POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:emborodo> $<TARGET_RUNTIME_DLLS:emborodo>
        COMMAND_EXPAND_LISTS)

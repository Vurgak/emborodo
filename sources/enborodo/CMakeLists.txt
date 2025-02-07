file(GLOB_RECURSE ENBORODO_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp)
add_library(enborodo)
target_sources(enborodo PRIVATE ${ENBORODO_SOURCES})
target_include_directories(enborodo PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(enborodo PUBLIC glad glfw glm::glm imgui magic_enum::magic_enum boost_pfr stb tinyobjloader tomlplusplus::tomlplusplus)

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

file(GLOB_RECURSE ENBORODO_TESTS CONFIGURE_DEPENDS *.cpp)
add_executable(enborodo_tests)
target_sources(enborodo_tests PRIVATE ${ENBORODO_TESTS})
target_link_libraries(enborodo_tests PRIVATE Catch2::Catch2WithMain enborodo)

add_custom_command(
        TARGET enborodo_tests POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy -t $<TARGET_FILE_DIR:enborodo_tests> $<TARGET_RUNTIME_DLLS:enborodo_tests>
        COMMAND_EXPAND_LISTS)

add_test(enborodo_tests enborodo_tests)

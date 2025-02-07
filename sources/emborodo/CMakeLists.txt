file(GLOB_RECURSE EMBORODO_SOURCES CONFIGURE_DEPENDS *.cpp *.hpp)
add_executable(emborodo)
target_sources(emborodo PRIVATE ${EMBORODO_SOURCES})
target_include_directories(emborodo PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
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

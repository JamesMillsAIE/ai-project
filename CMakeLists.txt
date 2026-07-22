cmake_minimum_required(VERSION 3.26)
project(dungeon_generator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (MSVC)
    add_compile_options(/Zc:preprocessor)
endif()

add_compile_definitions($<$<CONFIG:Debug>:_DEBUG>)

file(
    GLOB_RECURSE SOURCES CONFIGURE_DEPENDS
    "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h"
    "${CMAKE_CURRENT_SOURCE_DIR}/source/*cpp"
)

include(FetchContent)
add_executable(AIGame ${SOURCES})

FetchContent_Declare(
    glm
    GIT_REPOSITORY https://github.com/g-truc/glm.git
    GIT_TAG 1.0.3
)

FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 6.0
)

SET(GLM_TEST_ENABLE OFF CACHE BOOL "GLM Build unit tests")
set(BUILD_SHARED_LIBS OFF CACHE INTERNAL "Build shared libraries" FORCE)

FetchContent_MakeAvailable(glm)
FetchContent_MakeAvailable(raylib)

target_link_libraries(AIGame
    PUBLIC glm::glm
    PUBLIC raylib
)

target_include_directories(AIGame
    PUBLIC "include"
    PUBLIC ${CMAKE_CURRENT_BINARY_DIR}
)

add_custom_command(
    TARGET AIGame
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E echo "Copying resources..."
    COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/resources/" "$<TARGET_FILE_DIR:AIGame>/resources/"
)
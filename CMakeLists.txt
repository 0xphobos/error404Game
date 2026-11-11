cmake_minimum_required(VERSION 3.16)
project(RunAndGun LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.1
)
FetchContent_MakeAvailable(SFML)

# Toma automáticamente todos los .cpp dentro de src/
file(GLOB_RECURSE FUENTES CONFIGURE_DEPENDS src/*.cpp)

add_executable(RunAndGun ${FUENTES})
target_include_directories(RunAndGun PRIVATE src)
target_link_libraries(RunAndGun PRIVATE sfml-graphics sfml-window sfml-system)

# Copia assets y data junto al ejecutable
add_custom_command(TARGET RunAndGun POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:RunAndGun>/assets
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/data $<TARGET_FILE_DIR:RunAndGun>/data)
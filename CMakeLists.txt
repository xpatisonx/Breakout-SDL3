#cmake_minimum_required(VERSION 3.20)
#project(Breakout LANGUAGES CXX)
#
#set(CMAKE_CXX_STANDARD 20)
#set(CMAKE_CXX_STANDARD_REQUIRED ON)
#
## Ścieżka do SDL3
#set(SDL3_DIR ${CMAKE_SOURCE_DIR}/external/SDL3)
#
## Wymuś budowanie statycznej wersji SDL3
#set(SDL_SHARED OFF CACHE BOOL "Build SDL3 as a shared library" FORCE)
#set(SDL_STATIC ON CACHE BOOL "Build SDL3 as a static library" FORCE)
#set(SDL_TEST OFF CACHE BOOL "Disable SDL3 tests" FORCE)
#set(SDL_HIDAPI OFF CACHE BOOL "Disable HIDAPI support" FORCE)
#set(SDL_IME OFF CACHE BOOL "Disable IME support" FORCE)
#
## Dodaj SDL3 do projektu
#add_subdirectory(${SDL3_DIR} external/SDL3_build EXCLUDE_FROM_ALL)
#
#add_executable(Breakout src/main.cpp)
#target_link_libraries(Breakout PRIVATE SDL3-static)
#
#
#if (MINGW)
#    target_link_libraries(Breakout PRIVATE mingw32)
#    target_link_options(Breakout PRIVATE -static -static-libgcc -static-libstdc++)
#else ()
#    target_link_options(my_game PRIVATE -static)
#endif()

cmake_minimum_required(VERSION 3.20)
project(Breakout LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include the command that downloads libraries
include(FetchContent)

# define a function for adding git dependencies
function(include_dependency libName gitURL gitTag)
    # setup the declare
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG        ${gitTag}
            GIT_SHALLOW    TRUE
            GIT_PROGRESS   TRUE
    )

    FetchContent_MakeAvailable(${libName})
endfunction()

# add SDL3 support
find_package(SDL3 QUIET)
if (NOT SDL3_FOUND)
    message(STATUS "Getting SDL3 from Github")
    include_dependency(SDL3 https://github.com/libsdl-org/SDL.git release-3.2.0)
else()
    message(STATUS "Using local SDL3")
endif()

# add SDL2_ttf support
find_package(SDL3_ttf QUIET)
if (NOT SDL3_ttf_FOUND)
    message(STATUS "Getting SDL3_ttf from Github")
    include_dependency(SDL3_ttf https://github.com/libsdl-org/SDL_ttf.git preview-3.1.0)
else()
    message(STATUS "Using local SDL3_ttf")
endif()

add_executable(Breakout WIN32 src/main.cpp)

# set the include directory
target_include_directories(Breakout PUBLIC ${SDL3_INCLUDE_DIRS} ${SDL3_TTF_INCLUDE_DIRS})

target_compile_definitions(Breakout PRIVATE SDL_MAIN_USE_CALLBACKS)

# link all libraries to the project
target_link_libraries(Breakout PRIVATE SDL3::SDL3 SDL3_ttf::SDL3_ttf)

if (WIN32)
    add_custom_command(
            TARGET Breakout POST_BUILD
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:Breakout>"
            COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3_ttf::SDL3_ttf>" "$<TARGET_FILE_DIR:Breakout>"
            VERBATIM
    )
endif()
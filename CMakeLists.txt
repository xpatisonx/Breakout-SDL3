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

# add SDL3_ttf support
find_package(SDL3_ttf QUIET)
if (NOT SDL3_ttf_FOUND)
    message(STATUS "Getting SDL3_ttf from Github")
    include_dependency(SDL3_ttf https://github.com/libsdl-org/SDL_ttf.git preview-3.1.0)
else()
    message(STATUS "Using local SDL3_ttf")
endif()

add_executable(Breakout WIN32 src/main.cpp
        src/objects/GameObject.cpp
        src/Engine.cpp
        src/Level.cpp
        src/objects/Brick.cpp
        src/objects/Ball.cpp
        src/objects/Paddle.cpp
        src/objects/Bonus.cpp
        src/objects/ObjectContainer.cpp
        src/GameStats.cpp
)

# set the include directory
target_include_directories(Breakout PUBLIC ${SDL3_INCLUDE_DIRS} ${SDL3_TTF_INCLUDE_DIRS} PRIVATE api)

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
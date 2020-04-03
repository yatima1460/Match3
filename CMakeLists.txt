cmake_minimum_required(VERSION 3.5.1)


set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output)


# Create project
project(Match3)
set(CMAKE_CXX_STANDARD 14)
include_directories(Include)
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(Match3 ${SOURCES})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")







# Load SDL2
if(WIN32)
    # Windows
    
endif()

set(BUILD_TESTING OFF)
add_subdirectory(Vendor/entt)
include_directories(Vendor/entt/src)
target_link_libraries(Match3 ${ENTT_LIBRARY})

include_directories(Vendor/stb)

if (UNIX AND NOT APPLE AND NOT ANDROID)

    # Linux
    find_program(LSB_RELEASE_EXEC lsb_release)
    execute_process(COMMAND ${LSB_RELEASE_EXEC} -is OUTPUT_VARIABLE LSB_RELEASE_ID_SHORT OUTPUT_STRIP_TRAILING_WHITESPACE)
    message("Your distro is ${LSB_RELEASE_ID_SHORT}")
    find_package(SDL2 REQUIRED)
    if ("${LSB_RELEASE_ID_SHORT}" STREQUAL "Arch")
        message("Arch distro detected, using Arch CMake linkage")
        target_link_libraries(Match3 SDL2::SDL2)
    else ()
        message("Non-Arch distro detected, using normal linkage")
        string(STRIP ${SDL2_LIBRARIES} SDL2_LIBRARIES) # Fix because CMake is stupid, remove trailing spaces
        include_directories(Match3 ${SDL2_INCLUDE_DIRS})
        target_link_libraries(Match3 ${SDL2_LIBRARIES})
    endif ()

    # Load SDL2 extensions
    set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})
    find_package(SDL2TTF REQUIRED)
    include_directories(Match3 ${SDL2TTF_INCLUDE_DIR})
    target_link_libraries(Match3 ${SDL2TTF_LIBRARY})

endif()

# Copy Assets folder to build directory
file(COPY Assets DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

file(COPY Settings.ini DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

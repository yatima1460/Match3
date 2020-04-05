cmake_minimum_required(VERSION 3.5.1)

if(${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "Prevented in-tree built. Please create a build directory outside of the source code and call cmake from there. Thank you.")
endif()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Libraries)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Output)


# Create project
project(Match3)
set(CMAKE_CXX_STANDARD 11)
include_directories(Include)
file(GLOB_RECURSE SOURCES Source/*.cpp)
add_executable(Match3 ${SOURCES})





if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()


# Load SDL2
if(WIN32)
    # Windows

    if (MSVC)
        #add_compile_options("/std:c++14")

        add_definitions(-DNOMINMAX)

        include_directories(Vendor/windows_dirent)

        include_directories(Vendor/SDL2-devel-2.0.12-VC/include)
        include_directories(Vendor/SDL2_ttf-devel-2.0.15-VC/include)
        
        target_link_libraries(Match3 ${PROJECT_SOURCE_DIR}/Vendor/SDL2-devel-2.0.12-VC/lib/x64/SDL2.lib)
        target_link_libraries(Match3 ${PROJECT_SOURCE_DIR}/Vendor/SDL2_ttf-devel-2.0.15-VC/lib/x64/SDL2_ttf.lib)

        file(COPY ${PROJECT_SOURCE_DIR}/Vendor/SDL2-devel-2.0.12-VC/lib/x64/SDL2.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

        file(COPY ${PROJECT_SOURCE_DIR}/Vendor/SDL2_ttf-devel-2.0.15-VC/lib/x64/libfreetype-6.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        file(COPY ${PROJECT_SOURCE_DIR}/Vendor/SDL2_ttf-devel-2.0.15-VC/lib/x64/SDL2_ttf.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
        file(COPY ${PROJECT_SOURCE_DIR}/Vendor/SDL2_ttf-devel-2.0.15-VC/lib/x64/zlib1.dll DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
    endif()
endif()


add_subdirectory(Vendor/gulrak-filesystem)
include_directories(Vendor/gulrak-filesystem/include)
target_link_libraries(Match3 ghc_filesystem)

# add_subdirectory(Vendor/entt_cpp14)
# include_directories(Vendor/entt_cpp14/src)
# target_link_libraries(Match3 ${ENTT_LIBRARY})

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

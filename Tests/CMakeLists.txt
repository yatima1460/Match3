cmake_minimum_required(VERSION 3.10)

project(DP_Example)

if (CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic")
endif()

include(CTest)
set(CMAKE_CXX_STANDARD 11)

if (CMAKE_VERSION VERSION_LESS 3.2)
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "")
else ()
    set(UPDATE_DISCONNECTED_IF_AVAILABLE "UPDATE_DISCONNECTED 1")
endif ()

include(DownloadProject.cmake)
download_project(PROJ googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.10.0
        ${UPDATE_DISCONNECTED_IF_AVAILABLE}
        )




# Prevent GoogleTest from overriding our compiler/linker options
# when building with Visual Studio
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})

# When using CMake 2.8.11 or later, header path dependencies
# are automatically added to the gtest and gmock targets.
# For earlier CMake versions, we have to explicitly add the
# required directories to the header search path ourselves.
if (CMAKE_VERSION VERSION_LESS 2.8.11)
    include_directories("${gtest_SOURCE_DIR}/include"
            "${gmock_SOURCE_DIR}/include")
endif ()


file(GLOB_RECURSE SOURCES *.cpp ../Source/Game/*.cpp)

# Trivial example using gtest and gmock
add_executable(Match3Test ${SOURCES})

include_directories("../Include/Game")


target_link_libraries(Match3Test gtest gmock_main)

include(GoogleTest)


gtest_discover_tests(Match3Test)


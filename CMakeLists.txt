cmake_minimum_required(VERSION 3.26)
project(cpp_playground LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Automatically find all chapter files (cp*.cpp) in src/
file(GLOB CHAPTER_SOURCES "src/cp*.cpp")

# Create an executable for each chapter file
foreach(SOURCE_FILE ${CHAPTER_SOURCES})
    # Get filename without path and extension (e.g., cp1.cpp -> cp1)
    get_filename_component(EXEC_NAME ${SOURCE_FILE} NAME_WE)

    # Create executable
    add_executable(${EXEC_NAME} ${SOURCE_FILE})

    message(STATUS "Added target: ${EXEC_NAME}")
endforeach()
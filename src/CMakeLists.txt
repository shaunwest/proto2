cmake_minimum_required (VERSION 3.2)
project ("Proto2")

# GENERAL SETTINGS
# --------------------------------------------------------------------------------------
# The version number
set (Proto2_VERSION_MAJOR 1)
set (Proto2_VERSION_MINOR 0)

# Executable file
set (EXECUTABLE_NAME "proto2")

# OSX minimum version supported
set (CMAKE_OSX_DEPLOYMENT_TARGET 10.11.6)

# Export compile commands
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Get all source files in the source root
file (GLOB_RECURSE SRC_FILES "${PROJECT_SOURCE_DIR}/*.cpp" "${PROJECT_SOURCE_DIR}/*.c")
file (GLOB_RECURSE HEADER_FILES "${PROJECT_SOURCE_DIR}/*.h")

# MACROS
# --------------------------------------------------------------------------------------
# Put source/headers into source groups (for XCode/VStudio)
macro (SOURCE_GROUP_BY_FOLDER)
  foreach (file ${SRC_FILES} ${HEADER_FILES})
    file (RELATIVE_PATH relative_file "${PROJECT_SOURCE_DIR}" ${file})
    get_filename_component (dir "${relative_file}" DIRECTORY)
    source_group ("${dir}" FILES ${file})
  endforeach (file)
endmacro (SOURCE_GROUP_BY_FOLDER)

SOURCE_GROUP_BY_FOLDER()

# SOURCE
# --------------------------------------------------------------------------------------
# Configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${PROJECT_SOURCE_DIR}/app-config.h.in"
  "${PROJECT_BINARY_DIR}/app-config.h"
)

# Add the binary tree to the search path for include files
# so that we will find app-config.h
include_directories (${PROJECT_BINARY_DIR})

# Add source dir to include directories
include_directories (${PROJECT_SOURCE_DIR})

# EXECUTABLE
# --------------------------------------------------------------------------------------
add_executable (${EXECUTABLE_NAME} ${SRC_FILES} ${HEADER_FILES})
target_link_libraries (${EXECUTABLE_NAME} ${EXTRA_LIBS})

# C++11
set_target_properties(${EXECUTABLE_NAME} PROPERTIES
  CXX_STANDARD 11
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)


# COPY FILES
# --------------------------------------------------------------------------------------
add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
  "${CMAKE_SOURCE_DIR}/../assets" "$<TARGET_FILE_DIR:${EXECUTABLE_NAME}>/assets")


# EXTERNAL LIBRARIES
# --------------------------------------------------------------------------------------
# Find CMake Modules
set (CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/../cmake_modules" ${CMAKE_MODULE_PATH})

# SDL2
find_package(SDL2 REQUIRED)
include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries (${EXECUTABLE_NAME} ${SDL2_LIBRARY})

# SDL2 Image
find_package(SDL2_image REQUIRED)
include_directories(${SDL2IMAGE_INCLUDE_DIR})
target_link_libraries (${EXECUTABLE_NAME} ${SDL2IMAGE_LIBRARY})

# SDL2 TTF
find_package(SDL2ttf REQUIRED)
include_directories(${SDL2TTF_INCLUDE_DIR})
target_link_libraries (${EXECUTABLE_NAME} ${SDL2TTF_LIBRARY})

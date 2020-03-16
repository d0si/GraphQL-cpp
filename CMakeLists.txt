cmake_minimum_required(VERSION 3.10)
project(GraphQL-cpp
    LANGUAGES CXX
    VERSION 0.0.1
)

option(GRAPHQL_BUILD_SHARED_LIBS "Build shared libs when enabled otherwise static" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set cpp sources
set(GRAPHQL_SOURCES
    GraphQL/Parser/Parser.cpp
)

# Fallback to Release build if nothing else was chosen
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Build type will be 'Release'.")
  set(CMAKE_BUILD_TYPE Release CACHE STRING "Choose the type of build." FORCE)

  # Add possible build types
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
    "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

# Select library output type
if(GRAPHQL_BUILD_SHARED_LIBS)
    set(GRAPHQL_LIBRARY_TYPE SHARED)
else()
    set(GRAPHQL_LIBRARY_TYPE STATIC)
endif()

# Add target library
add_library(graphql ${GRAPHQL_LIBRARY_TYPE}
    ${GRAPHQL_SOURCES}
)

# Add include directories
target_include_directories(graphql
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

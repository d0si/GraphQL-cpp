cmake_minimum_required(VERSION 3.10)
project(GraphQL-cpp
    LANGUAGES CXX
    VERSION 0.0.1
)

option(GRAPHQLPARSER_BUILD_SHARED_LIBS "Build shared libs for parser when enabled otherwise static" OFF)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(GraphQLParser)

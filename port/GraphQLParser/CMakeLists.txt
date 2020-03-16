# Set cpp sources
set(GRAPHQLPARSER_SOURCES
    GraphQLParser/Lexer1.cpp
    GraphQLParser/LexerContext.cpp
    GraphQLParser/Location.cpp
    GraphQLParser/Parser.cpp
    GraphQLParser/ParserContext.cpp
    GraphQLParser/Source.cpp
    GraphQLParser/Token.cpp

    GraphQLParser/AST/ASTNode.cpp
    GraphQLParser/AST/GraphQLArgument.cpp
    GraphQLParser/AST/GraphQLComment.cpp
    GraphQLParser/AST/GraphQLDirective.cpp
    GraphQLParser/AST/GraphQLDirectiveDefinition.cpp
    GraphQLParser/AST/GraphQLDocument.cpp
    GraphQLParser/AST/GraphQLEnumTypeDefinition.cpp
    GraphQLParser/AST/GraphQLEnumValueDefinition.cpp
    GraphQLParser/AST/GraphQLFieldDefinition.cpp
    GraphQLParser/AST/GraphQLFieldSelection.cpp
    GraphQLParser/AST/GraphQLFragmentDefinition.cpp
    GraphQLParser/AST/GraphQLFragmentSpread.cpp
    GraphQLParser/AST/GraphQLInlineFragment.cpp
    GraphQLParser/AST/GraphQLInputObjectTypeDefinition.cpp
    GraphQLParser/AST/GraphQLInputValueDefinition.cpp
    GraphQLParser/AST/GraphQLInterfaceTypeDefinition.cpp
    GraphQLParser/AST/GraphQLListType.cpp
    GraphQLParser/AST/GraphQLListValue.cpp
    GraphQLParser/AST/GraphQLLocation.cpp
    GraphQLParser/AST/GraphQLName.cpp
    GraphQLParser/AST/GraphQLNamedType.cpp
    GraphQLParser/AST/GraphQLNonNullType.cpp
    GraphQLParser/AST/GraphQLObjectField.cpp
    GraphQLParser/AST/GraphQLObjectTypeDefinition.cpp
    GraphQLParser/AST/GraphQLObjectValue.cpp
    GraphQLParser/AST/GraphQLOperationDefinition.cpp
    GraphQLParser/AST/GraphQLOperationTypeDefinition.cpp
    GraphQLParser/AST/GraphQLScalarTypeDefinition.cpp
    GraphQLParser/AST/GraphQLScalarValue.cpp
    GraphQLParser/AST/GraphQLSchemaDefinition.cpp
    GraphQLParser/AST/GraphQLSelectionSet.cpp
    GraphQLParser/AST/GraphQLType.cpp
    GraphQLParser/AST/GraphQLTypeDefinition.cpp
    GraphQLParser/AST/GraphQLTypeExtensionDefinition.cpp
    GraphQLParser/AST/GraphQLUnionTypeDefinition.cpp
    GraphQLParser/AST/GraphQLValue.cpp
    GraphQLParser/AST/GraphQLVariable.cpp
    GraphQLParser/AST/GraphQLVariableDefinition.cpp

    GraphQLParser/Exceptions/GraphQLSyntaxErrorException.cpp
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
if(GRAPHQLPARSER_BUILD_SHARED_LIBS)
    set(GRAPHQLPARSER_LIBRARY_TYPE SHARED)
else()
    set(GRAPHQLPARSER_LIBRARY_TYPE STATIC)
endif()

# Add target library
add_library(graphqlparser ${GRAPHQLPARSER_LIBRARY_TYPE}
    ${GRAPHQLPARSER_SOURCES}
)

# Add include directories
target_include_directories(graphqlparser
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}
)

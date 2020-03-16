#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLFieldDefinition.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLObjectTypeDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLObjectTypeDefinition();
			GraphQLObjectTypeDefinition(
				std::shared_ptr<GraphQLName> name,
				std::vector<GraphQLNamedType> interfaces,
				std::vector<GraphQLDirective> directives,
				std::vector<GraphQLFieldDefinition> fields
			);

			std::vector<GraphQLNamedType> Interfaces;

			std::vector<GraphQLDirective> Directives;

			std::vector<GraphQLFieldDefinition> Fields;

		};
	}
}

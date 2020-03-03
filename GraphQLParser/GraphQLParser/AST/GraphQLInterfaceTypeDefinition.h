#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLFieldDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLInterfaceTypeDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLInterfaceTypeDefinition();
			GraphQLInterfaceTypeDefinition(GraphQLName name, std::vector<GraphQLDirective> directives, std::vector<AST::GraphQLFieldDefinition> fields);

			std::vector<GraphQLDirective> Directives;

			std::vector<AST::GraphQLFieldDefinition> Fields;
		};
	}
}

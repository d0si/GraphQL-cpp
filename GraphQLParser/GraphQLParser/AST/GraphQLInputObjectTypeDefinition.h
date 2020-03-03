#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLInputObjectTypeDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLInputObjectTypeDefinition();
			GraphQLInputObjectTypeDefinition(GraphQLName name, std::vector<GraphQLDirective> directives, std::vector<GraphQLInputValueDefinition> fields);

			std::vector<GraphQLDirective> Directives;

			std::vector<GraphQLInputValueDefinition> Fields;
		};
	}
}

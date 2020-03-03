#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>
#include <GraphQLParser/AST/GraphQLType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFieldDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLFieldDefinition();
			GraphQLFieldDefinition(
				GraphQLName name,
				std::vector<GraphQLInputValueDefinition> arguments,
				GraphQLType type,
				std::vector<GraphQLDirective> directives);

			std::vector<GraphQLInputValueDefinition> Arguments;

			GraphQLType Type;

			std::vector<GraphQLDirective> Directives;
		};
	}
}

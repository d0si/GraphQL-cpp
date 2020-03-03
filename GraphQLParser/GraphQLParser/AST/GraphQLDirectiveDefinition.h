#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDirectiveDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLDirectiveDefinition();
			GraphQLDirectiveDefinition(GraphQLName name, bool repeatable, std::vector<GraphQLInputValueDefinition> arguments, std::vector<GraphQLName> locations);

			bool Repeatable;

			std::vector<GraphQLInputValueDefinition> Arguments;

			std::vector<GraphQLName> Locations;
		};
	}
}

#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDirectiveDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLDirectiveDefinition();
			GraphQLDirectiveDefinition(std::shared_ptr<GraphQLName> name, bool repeatable, std::vector<GraphQLInputValueDefinition> arguments, std::vector<std::shared_ptr<GraphQLName>> locations);

			bool Repeatable;

			std::vector<GraphQLInputValueDefinition> Arguments;

			std::vector<std::shared_ptr<GraphQLName>> Locations;
		};
	}
}

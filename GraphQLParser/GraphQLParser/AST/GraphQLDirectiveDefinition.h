#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDirectiveDefinition : public GraphQLTypeDefinition {
		public:
			ASTNodeKind Kind = ASTNodeKind::DirectiveDefinition;

			std::vector<GraphQLInputValueDefinition> Arguments;

			std::vector<GraphQLInputValueDefinition> Definitions;

			std::vector<GraphQLName> Locations;

			bool Repeatable;
		};
	}
}

#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLScalarTypeDefinition: public GraphQLTypeDefinition {
		public:
			std::vector<GraphQLDirective> Directives;

			ASTNodeKind Kind = ASTNodeKind::ScalarTypeDefinition;
		};
	}
}

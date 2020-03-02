#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLArgument.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLName.h>
#include <GraphQLParser/AST/GraphQLSelectionSet.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFieldSelection : public ASTNode {
		public:
			GraphQLName Alias;

			std::vector<GraphQLArgument> Arguments;

			std::vector<GraphQLDirective> Directives;

			ASTNodeKind Kind = ASTNodeKind::Field;

			GraphQLName Name;

			GraphQLSelectionSet SelectionSet;
		};
	}
}

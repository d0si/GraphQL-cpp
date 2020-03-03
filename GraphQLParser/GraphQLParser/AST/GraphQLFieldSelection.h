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
			GraphQLFieldSelection();
			GraphQLFieldSelection(
				GraphQLName alias,
				GraphQLName name,
				std::vector<GraphQLArgument> arguments,
				std::vector<GraphQLDirective> directives,
				GraphQLSelectionSet selection_set);

			GraphQLName Alias;

			GraphQLName Name;

			std::vector<GraphQLArgument> Arguments;

			std::vector<GraphQLDirective> Directives;

			GraphQLSelectionSet SelectionSet;
		};
	}
}

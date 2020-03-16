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
				std::shared_ptr<GraphQLName> alias,
				std::shared_ptr<GraphQLName> name,
				std::vector<GraphQLArgument> arguments,
				std::vector<GraphQLDirective> directives,
				GraphQLSelectionSet selection_set);

			std::shared_ptr<GraphQLName> Alias;

			std::shared_ptr<GraphQLName> Name;

			std::vector<GraphQLArgument> Arguments;

			std::vector<GraphQLDirective> Directives;

			GraphQLSelectionSet SelectionSet;
		};
	}
}

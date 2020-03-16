#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLSelectionSet.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLInlineFragment : public ASTNode {
		public:
			GraphQLInlineFragment();
			GraphQLInlineFragment(ASTNodeKind kind);
			GraphQLInlineFragment(GraphQLNamedType type_condition, std::vector<GraphQLDirective> directives, GraphQLSelectionSet selection_set);
			GraphQLInlineFragment(ASTNodeKind kind, GraphQLNamedType type_condition, std::vector<GraphQLDirective> directives, GraphQLSelectionSet selection_set);

			std::vector<GraphQLDirective> Directives;

			GraphQLSelectionSet SelectionSet;

			GraphQLNamedType TypeCondition;
		};
	}
}

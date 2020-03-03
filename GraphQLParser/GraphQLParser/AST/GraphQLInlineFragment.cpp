#include <GraphQLParser/AST/GraphQLInlineFragment.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLInlineFragment::GraphQLInlineFragment() : ASTNode(ASTNodeKind::InlineFragment) {

		}

		GraphQLInlineFragment::GraphQLInlineFragment(ASTNodeKind kind) : ASTNode(kind) {

		}

		GraphQLInlineFragment::GraphQLInlineFragment(GraphQLNamedType type_condition, std::vector<GraphQLDirective> directives, GraphQLSelectionSet selection_set)
			: ASTNode(ASTNodeKind::InlineFragment), TypeCondition(type_condition), Directives(directives), SelectionSet(selection_set) {

		}

		GraphQLInlineFragment::GraphQLInlineFragment(ASTNodeKind kind, GraphQLNamedType type_condition, std::vector<GraphQLDirective> directives, GraphQLSelectionSet selection_set)
			: ASTNode(kind), TypeCondition(type_condition), Directives(directives), SelectionSet(selection_set) {

		}
	}
}

#include <GraphQLParser/AST/GraphQLFragmentDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLFragmentDefinition::GraphQLFragmentDefinition() : GraphQLInlineFragment(ASTNodeKind::FragmentDefinition) {

		}

		GraphQLFragmentDefinition::GraphQLFragmentDefinition(std::shared_ptr<GraphQLName> name, GraphQLNamedType type_condition, std::vector<GraphQLDirective> directives, GraphQLSelectionSet selection_set)
			: GraphQLInlineFragment(ASTNodeKind::FragmentDefinition, type_condition, directives, selection_set), Name(name) {

		}
	}
}

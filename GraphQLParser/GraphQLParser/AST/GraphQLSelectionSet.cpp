#include <GraphQLParser/AST/GraphQLSelectionSet.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLSelectionSet::GraphQLSelectionSet() : ASTNode(ASTNodeKind::SelectionSet) {

		}

		GraphQLSelectionSet::GraphQLSelectionSet(std::vector<ASTNode> selections)
			: ASTNode(ASTNodeKind::SelectionSet), Selections(selections) {

		}
	}
}

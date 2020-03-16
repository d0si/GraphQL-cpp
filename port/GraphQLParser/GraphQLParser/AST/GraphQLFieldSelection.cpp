#include <GraphQLParser/AST/GraphQLFieldSelection.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLFieldSelection::GraphQLFieldSelection() : ASTNode(ASTNodeKind::Field) {

		}
		GraphQLFieldSelection::GraphQLFieldSelection(
			std::shared_ptr<GraphQLName> alias,
			std::shared_ptr<GraphQLName> name,
			std::vector<GraphQLArgument> arguments,
			std::vector<GraphQLDirective> directives,
			GraphQLSelectionSet selection_set)
			: ASTNode(ASTNodeKind::Field), Alias(alias), Name(name), Arguments(arguments), Directives(directives), SelectionSet(selection_set) {

		}
	}
}

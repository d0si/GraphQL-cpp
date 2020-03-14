#include <GraphQLParser/AST/GraphQLOperationDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLOperationDefinition::GraphQLOperationDefinition() : ASTNode(ASTNodeKind::OperationDefinition) {

		}

		GraphQLOperationDefinition::GraphQLOperationDefinition(OperationType operation, GraphQLSelectionSet selection_set)
			: ASTNode(ASTNodeKind::OperationDefinition), Operation(operation), SelectionSet(selection_set) {

		}

		GraphQLOperationDefinition::GraphQLOperationDefinition(
			OperationType operation,
			std::shared_ptr<GraphQLName> name,
			std::vector<GraphQLVariableDefinition> variable_definitions,
			std::vector<GraphQLDirective> directives,
			GraphQLSelectionSet selection_set
		) : ASTNode(ASTNodeKind::OperationDefinition), Operation(operation), Name(name),
			VariableDefinitions(variable_definitions), Directives(directives), SelectionSet(selection_set) {

		}
	}
}

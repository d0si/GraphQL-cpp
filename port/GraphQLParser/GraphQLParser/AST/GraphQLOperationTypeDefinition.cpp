#include <GraphQLParser/AST/GraphQLOperationTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLOperationTypeDefinition::GraphQLOperationTypeDefinition() : ASTNode(ASTNodeKind::OperationTypeDefinition) {

		}

		GraphQLOperationTypeDefinition::GraphQLOperationTypeDefinition(OperationType operation, GraphQLNamedType type)
			: ASTNode(ASTNodeKind::OperationTypeDefinition), Operation(operation), Type(type) {

		}
	}
}

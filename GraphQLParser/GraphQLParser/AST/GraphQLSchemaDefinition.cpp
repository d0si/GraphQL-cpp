#include <GraphQLParser/AST/GraphQLSchemaDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLSchemaDefinition::GraphQLSchemaDefinition(std::vector<GraphQLDirective> directives, std::vector<GraphQLOperationTypeDefinition> operation_types)
			: ASTNode(ASTNodeKind::SchemaDefinition), Directives(directives), OperationTypes(operation_types) {

		}
	}
}

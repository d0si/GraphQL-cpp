#include <GraphQLParser/AST/GraphQLVariableDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLVariableDefinition::GraphQLVariableDefinition(std::shared_ptr<GraphQLVariable> variable, GraphQLType type, std::shared_ptr<GraphQLValue> default_value)
			: ASTNode(ASTNodeKind::VariableDefinition), Variable(variable), Type(type), DefaultValue(default_value) {

		}
	}
}

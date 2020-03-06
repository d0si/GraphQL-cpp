#include <GraphQLParser/AST/GraphQLVariableDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLVariableDefinition::GraphQLVariableDefinition(GraphQLVariable* variable, GraphQLType type, GraphQLValue* default_value)
			: ASTNode(ASTNodeKind::VariableDefinition), Variable(variable), Type(type), DefaultValue(default_value) {

		}
	}
}

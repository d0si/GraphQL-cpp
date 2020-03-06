#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLInputValueDefinition::GraphQLInputValueDefinition() : GraphQLTypeDefinition(ASTNodeKind::InputValueDefinition) {

		}

		GraphQLInputValueDefinition::GraphQLInputValueDefinition(GraphQLName name, GraphQLType type, GraphQLValue* default_value, std::vector<GraphQLDirective> directives)
			: GraphQLTypeDefinition(ASTNodeKind::InputValueDefinition, name), Type(type), DefaultValue(default_value), Directives(directives) {

		}
	}
}

#include <GraphQLParser/AST/GraphQLFieldDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLFieldDefinition::GraphQLFieldDefinition() : GraphQLTypeDefinition(ASTNodeKind::FieldDefinition) {

		}

		GraphQLFieldDefinition::GraphQLFieldDefinition(
			GraphQLName name,
			std::vector<GraphQLInputValueDefinition> arguments,
			GraphQLType type,
			std::vector<GraphQLDirective> directives)
			: GraphQLTypeDefinition(ASTNodeKind::FieldDefinition, name), Arguments(arguments), Type(type), Directives(directives) {

		}
	}
}

#include <GraphQLParser/AST/GraphQLInputObjectTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLInputObjectTypeDefinition::GraphQLInputObjectTypeDefinition() : GraphQLTypeDefinition(ASTNodeKind::InputObjectTypeDefinition) {

		}

		GraphQLInputObjectTypeDefinition::GraphQLInputObjectTypeDefinition(GraphQLName name, std::vector<GraphQLDirective> directives, std::vector<GraphQLInputValueDefinition> fields)
			: GraphQLTypeDefinition(ASTNodeKind::InputObjectTypeDefinition, name), Directives(directives), Fields(fields) {

		}
	}
}

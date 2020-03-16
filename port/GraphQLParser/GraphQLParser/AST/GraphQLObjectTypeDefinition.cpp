#include <GraphQLParser/AST/GraphQLObjectTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLObjectTypeDefinition::GraphQLObjectTypeDefinition() : GraphQLTypeDefinition(ASTNodeKind::ObjectTypeDefinition) {

		}

		GraphQLObjectTypeDefinition::GraphQLObjectTypeDefinition(
			std::shared_ptr<GraphQLName> name,
			std::vector<GraphQLNamedType> interfaces,
			std::vector<GraphQLDirective> directives,
			std::vector<GraphQLFieldDefinition> fields)
			: GraphQLTypeDefinition(ASTNodeKind::ObjectTypeDefinition, name), Interfaces(interfaces), Directives(directives), Fields(fields) {

		}
	}
}

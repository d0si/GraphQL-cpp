#include <GraphQLParser/AST/GraphQLInterfaceTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLInterfaceTypeDefinition::GraphQLInterfaceTypeDefinition() : GraphQLTypeDefinition(ASTNodeKind::InterfaceTypeDefinition) {

		}

		GraphQLInterfaceTypeDefinition::GraphQLInterfaceTypeDefinition(GraphQLName name, std::vector<GraphQLDirective> directives, std::vector<AST::GraphQLFieldDefinition> fields)
			: GraphQLTypeDefinition(ASTNodeKind::InterfaceTypeDefinition, name), Directives(directives), Fields(fields) {

		}
	}
}

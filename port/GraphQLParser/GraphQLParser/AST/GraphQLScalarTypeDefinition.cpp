#include <GraphQLParser/AST/GraphQLScalarTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLScalarTypeDefinition::GraphQLScalarTypeDefinition() : GraphQLTypeDefinition(ASTNodeKind::ScalarTypeDefinition) {

		}

		GraphQLScalarTypeDefinition::GraphQLScalarTypeDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives)
			: GraphQLTypeDefinition(ASTNodeKind::ScalarTypeDefinition, name), Directives(directives) {

		}
	}
}

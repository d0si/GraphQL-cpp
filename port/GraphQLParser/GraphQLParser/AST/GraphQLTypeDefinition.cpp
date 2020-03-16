#include <GraphQLParser/AST/GraphQLTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLTypeDefinition::GraphQLTypeDefinition() {

		}

		GraphQLTypeDefinition::GraphQLTypeDefinition(ASTNodeKind kind) : ASTNode(kind) {

		}

		GraphQLTypeDefinition::GraphQLTypeDefinition(ASTNodeKind kind, std::shared_ptr<GraphQLName> name) : ASTNode(kind), Name(name) {

		}

	}
}

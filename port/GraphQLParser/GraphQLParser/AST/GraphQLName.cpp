#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLName::GraphQLName() : ASTNode(ASTNodeKind::Name) {

		}

		GraphQLName::GraphQLName(std::string value) : ASTNode(ASTNodeKind::Name), Value(value) {

		}
	}
}

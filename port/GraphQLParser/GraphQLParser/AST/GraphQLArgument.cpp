#include <GraphQLParser/AST/GraphQLArgument.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLArgument::GraphQLArgument() : ASTNode(ASTNodeKind::Argument) {

		}

		GraphQLArgument::GraphQLArgument(std::shared_ptr<GraphQLName> name, std::shared_ptr<GraphQLValue> value) : ASTNode(ASTNodeKind::Argument), Name(name), Value(value) {

		}
	}
}

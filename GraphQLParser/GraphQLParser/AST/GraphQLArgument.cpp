#include <GraphQLParser/AST/GraphQLArgument.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLArgument::GraphQLArgument() : ASTNode(ASTNodeKind::Argument) {

		}

		GraphQLArgument::GraphQLArgument(GraphQLName name, GraphQLValue* value) : ASTNode(ASTNodeKind::Argument), Name(name), Value(value) {

		}
	}
}

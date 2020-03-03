#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLValue::GraphQLValue() {

		}

		GraphQLValue::GraphQLValue(ASTNodeKind kind) : ASTNode(kind) {

		}
	}
}

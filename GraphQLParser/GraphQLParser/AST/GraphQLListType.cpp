#include <GraphQLParser/AST/GraphQLListType.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLListType::GraphQLListType(GraphQLType type) : GraphQLType(ASTNodeKind::ListType), Type(type) {

		}
	}
}

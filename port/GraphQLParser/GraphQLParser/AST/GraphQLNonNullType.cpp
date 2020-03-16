#include <GraphQLParser/AST/GraphQLNonNullType.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLNonNullType::GraphQLNonNullType() : GraphQLType(ASTNodeKind::NonNullType) {

		}

		GraphQLNonNullType::GraphQLNonNullType(GraphQLType type) : GraphQLType(ASTNodeKind::NonNullType), Type(type) {

		}
	}
}

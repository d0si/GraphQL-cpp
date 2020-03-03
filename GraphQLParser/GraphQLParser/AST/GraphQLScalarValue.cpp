#include <GraphQLParser/AST/GraphQLScalarValue.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLScalarValue::GraphQLScalarValue(ASTNodeKind kind, std::string value) : GraphQLValue(kind), Value(value) {

		}
	}
}

#include <GraphQLParser/AST/GraphQLListValue.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLListValue::GraphQLListValue(ASTNodeKind kind) : GraphQLValue(kind) {

		}

		GraphQLListValue::GraphQLListValue(ASTNodeKind kind, std::vector<GraphQLValue> values) : GraphQLValue(kind), Values(values) {

		}
	}
}

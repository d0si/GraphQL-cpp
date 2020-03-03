#include <GraphQLParser/AST/GraphQLObjectValue.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLObjectValue::GraphQLObjectValue() : GraphQLValue(ASTNodeKind::ObjectValue) {

		}

		GraphQLObjectValue::GraphQLObjectValue(std::vector<GraphQLObjectField> fields)
			: GraphQLValue(ASTNodeKind::ObjectValue), Fields(fields) {

		}
	}
}

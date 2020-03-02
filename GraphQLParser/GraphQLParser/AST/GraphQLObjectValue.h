#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLValue.h>
#include <GraphQLParser/AST/GraphQLObjectField.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLObjectValue : public GraphQLValue {
		public:
			std::vector<GraphQLObjectField> Fields;

			ASTNodeKind Kind = ASTNodeKind::ObjectValue;
		};
	}
}

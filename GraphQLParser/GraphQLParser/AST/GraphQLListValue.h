#pragma once

#include <vector>
#include <string>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLListValue : public GraphQLValue {
		public:
			GraphQLListValue(ASTNodeKind kind);
			GraphQLListValue(ASTNodeKind kind, std::vector<GraphQLValue*> values);

			std::string AstValue;

			std::vector<GraphQLValue*> Values;
		};
	}
}

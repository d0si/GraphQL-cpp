#pragma once

#include <memory>
#include <vector>
#include <string>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLListValue : public GraphQLValue {
		public:
			GraphQLListValue(ASTNodeKind kind);
			GraphQLListValue(ASTNodeKind kind, std::vector<std::shared_ptr<GraphQLValue>> values);

			std::string AstValue;

			std::vector<std::shared_ptr<GraphQLValue>> Values;
		};
	}
}

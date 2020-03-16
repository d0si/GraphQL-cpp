#pragma once

#include <string>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLScalarValue : public GraphQLValue {
		public:
			GraphQLScalarValue(ASTNodeKind kind, std::string value);

			std::string Value;
		};
	}
}

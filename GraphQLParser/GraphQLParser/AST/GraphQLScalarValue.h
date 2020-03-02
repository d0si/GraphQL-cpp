#pragma once

#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLScalarValue : public GraphQLValue {
		public:
			std::string Value;
		};
	}
}

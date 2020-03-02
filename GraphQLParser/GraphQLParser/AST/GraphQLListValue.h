#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLListValue : public GraphQLValue {
		public:
			std::string AstValue;

			std::vector<GraphQLValue> Values;
		};
	}
}

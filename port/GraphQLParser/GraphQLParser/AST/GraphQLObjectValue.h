#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLValue.h>
#include <GraphQLParser/AST/GraphQLObjectField.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLObjectValue : public GraphQLValue {
		public:
			GraphQLObjectValue();
			GraphQLObjectValue(std::vector<GraphQLObjectField> fields);

			std::vector<GraphQLObjectField> Fields;
		};
	}
}

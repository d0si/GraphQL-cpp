#pragma once

#include <GraphQLParser/AST/GraphQLType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLListType : public GraphQLType {
		public:
			GraphQLListType(GraphQLType type);

			GraphQLType Type;
		};
	}
}

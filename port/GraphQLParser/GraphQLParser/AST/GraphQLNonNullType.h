#pragma once

#include <GraphQLParser/AST/GraphQLType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLNonNullType : public GraphQLType {
		public:
			GraphQLNonNullType();
			GraphQLNonNullType(GraphQLType type);

			GraphQLType Type;
		};
	}
}

#pragma once

#include <GraphQLParser/AST/GraphQLValue.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLVariable : public GraphQLValue {
		public:
			GraphQLVariable(GraphQLName name);

			GraphQLName Name;
		};
	}
}

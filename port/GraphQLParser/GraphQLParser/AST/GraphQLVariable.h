#pragma once

#include <GraphQLParser/AST/GraphQLValue.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLVariable : public GraphQLValue {
		public:
			GraphQLVariable(std::shared_ptr<GraphQLName> name);

			std::shared_ptr<GraphQLName> Name;
		};
	}
}

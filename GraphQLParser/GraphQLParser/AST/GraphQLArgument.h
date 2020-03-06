#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLArgument : public ASTNode {
		public:
			GraphQLArgument();
			GraphQLArgument(GraphQLName name, GraphQLValue* value);

			GraphQLName Name;

			GraphQLValue* Value;
		};
	}
}

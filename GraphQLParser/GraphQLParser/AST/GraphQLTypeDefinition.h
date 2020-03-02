#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLTypeDefinition : public ASTNode {
		public:
			GraphQLName Name;
		};
	}
}

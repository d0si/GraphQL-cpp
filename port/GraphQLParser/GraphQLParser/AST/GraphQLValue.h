#pragma once

#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLValue : public ASTNode {
		public:
			GraphQLValue();
			GraphQLValue(ASTNodeKind kind);
		};
	}
}

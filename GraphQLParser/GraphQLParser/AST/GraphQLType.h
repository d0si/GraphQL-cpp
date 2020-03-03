#pragma once

#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLType : public ASTNode {
		public:
			GraphQLType();
			GraphQLType(ASTNodeKind kind);
		};
	}
}

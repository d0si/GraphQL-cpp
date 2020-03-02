#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDocument : public ASTNode {
		public:
			std::vector<ASTNode> Definitions;

			ASTNodeKind Kind = ASTNodeKind::Document;
		};
	}
}

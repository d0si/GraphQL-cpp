#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLSelectionSet : public ASTNode {
		public:
			ASTNodeKind Kind = ASTNodeKind::SelectionSet;

			std::vector<ASTNode> Selections;
		};
	}
}

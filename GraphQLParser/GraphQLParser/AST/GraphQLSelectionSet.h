#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLSelectionSet : public ASTNode {
		public:
			GraphQLSelectionSet();
			GraphQLSelectionSet(std::vector<ASTNode> selections);

			std::vector<ASTNode> Selections;
		};
	}
}

#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDocument : public ASTNode {
		public:
			GraphQLDocument();
			GraphQLDocument(std::vector<ASTNode*> definitions);

			std::vector<ASTNode*> Definitions;
		};
	}
}

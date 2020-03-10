#pragma once

#include <memory>
#include <vector>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDocument : public ASTNode {
		public:
			GraphQLDocument();
			GraphQLDocument(std::vector<std::shared_ptr<ASTNode>> definitions);

			std::vector<std::shared_ptr<ASTNode>> Definitions;
		};
	}
}

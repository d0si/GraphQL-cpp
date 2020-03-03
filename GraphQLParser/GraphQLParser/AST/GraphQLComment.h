#pragma once

#include <string>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLComment : public ASTNode {
		public:
			GraphQLComment();
			GraphQLComment(std::string text);

			std::string Text;
		};
	}
}

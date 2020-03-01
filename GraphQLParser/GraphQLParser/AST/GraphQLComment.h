#pragma once

#include <string>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLComment : public ASTNode {
		public:
			GraphQLComment(std::string text) : Text(text) {

			}

			ASTNodeKind Kind = ASTNodeKind::Comment;

			std::string Text;
		};
	}
}

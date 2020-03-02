#pragma once

#include <string>
#include <GraphQLParser/AST/ASTNode.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLComment : public ASTNode {
		public:
			ASTNodeKind Kind = ASTNodeKind::Comment;

			std::string Text;
		};
	}
}

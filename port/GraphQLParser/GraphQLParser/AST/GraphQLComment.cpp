#include <GraphQLParser/AST/GraphQLComment.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLComment::GraphQLComment() : ASTNode(ASTNodeKind::Comment) {

		}

		GraphQLComment::GraphQLComment(std::string text) : ASTNode(ASTNodeKind::Comment), Text(text) {

		}
	}
}

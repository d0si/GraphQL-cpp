#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLComment.h>

namespace GraphQLParser {
	namespace AST {
		ASTNode::ASTNode() : ASTNode(ASTNodeKind::Name) {

		}

		ASTNode::ASTNode(ASTNodeKind kind) : ASTNode(kind, GraphQLLocation(0, 0)) {

		}

		ASTNode::ASTNode(ASTNodeKind kind, GraphQLLocation location) : Kind(kind), Location(location) {

		}

		ASTNode::~ASTNode() {
			if (Comment != nullptr) {
				delete Comment;
			}
		}

		void ASTNode::set_comment(GraphQLComment comment) {
			if (Comment != nullptr) {
				delete Comment;
			}

			Comment = new GraphQLComment();
			*Comment = comment;
		}
	}
}

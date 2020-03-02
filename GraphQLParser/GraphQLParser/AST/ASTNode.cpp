#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLComment.h>

namespace GraphQLParser {
	namespace AST {
		ASTNode::ASTNode() : Location(0, 0) {

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

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

		ASTNode::ASTNode(ASTNodeKind kind, GraphQLLocation location, std::shared_ptr<GraphQLComment> comment) : Kind(kind), Location(location), Comment(comment) {

		}

		ASTNode::~ASTNode() {

		}
	}
}

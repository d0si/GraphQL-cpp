#include <GraphQLParser/AST/GraphQLDocument.h>

namespace GraphQLParser {
	namespace AST {
		GraphQLDocument::GraphQLDocument() : ASTNode(ASTNodeKind::Document) {

		}

		GraphQLDocument::GraphQLDocument(std::vector<std::shared_ptr<ASTNode>> definitions) : ASTNode(ASTNodeKind::Document), Definitions(definitions) {

		}
	}
}

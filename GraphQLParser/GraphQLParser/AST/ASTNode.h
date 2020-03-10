#pragma once

#include <memory>
#include <GraphQLParser/AST/Enums.h>
#include <GraphQLParser/AST/GraphQLLocation.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLComment;

		class ASTNode {
		public:
			ASTNode();
			ASTNode(ASTNodeKind kind);
			ASTNode(ASTNodeKind kind, GraphQLLocation location);
			~ASTNode();
			
			void set_comment(GraphQLComment comment);

			ASTNodeKind Kind;
			GraphQLLocation Location;
			std::shared_ptr<GraphQLComment> Comment;
		};
	}
}

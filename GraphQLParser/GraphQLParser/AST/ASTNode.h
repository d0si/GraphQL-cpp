#pragma once

#include <GraphQLParser/AST/Enums.h>
#include <GraphQLParser/AST/GraphQLLocation.h>
//#include <GraphQLParser/AST/GraphQLComment.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLComment;

		class ASTNode {
		public:
			ASTNode();
			~ASTNode();
			
			void set_comment(GraphQLComment comment);

			ASTNodeKind Kind;
			GraphQLLocation Location;
			GraphQLComment* Comment;
		};
	}
}

#pragma once

#include <GraphQLParser/AST/Enums.h>
#include <GraphQLParser/AST/GraphQLLocation.h>
#include <GraphQLParser/AST/GraphQLComment.h>

namespace GraphQLParser {
	namespace AST {
		class ASTNode {
		public:
			ASTNode();

			ASTNodeKind Kind;
			GraphQLLocation Location;
			GraphQLComment Comment;
		};
	}
}
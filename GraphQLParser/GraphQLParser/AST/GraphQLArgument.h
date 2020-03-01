#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLArgument : public ASTNode {
		public:
			ASTNodeKind Kind = ASTNodeKind::Argument;

			GraphQLName Name;

			GraphQLValue Value;
		};
	}
}

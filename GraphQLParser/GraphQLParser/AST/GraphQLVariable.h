#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLVariable : public ASTNode {
		public:
			ASTNodeKind Kind = ASTNodeKind::Variable;

			GraphQLName Name;
		};
	}
}

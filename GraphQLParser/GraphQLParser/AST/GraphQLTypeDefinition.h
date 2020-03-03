#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLTypeDefinition : public ASTNode {
		public:
			GraphQLTypeDefinition();
			GraphQLTypeDefinition(ASTNodeKind kind);
			GraphQLTypeDefinition(ASTNodeKind kind, GraphQLName name);

			GraphQLName Name;
		};
	}
}

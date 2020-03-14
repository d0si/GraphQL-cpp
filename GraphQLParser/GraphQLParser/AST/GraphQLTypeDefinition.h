#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLTypeDefinition : public ASTNode {
		public:
			GraphQLTypeDefinition();
			GraphQLTypeDefinition(ASTNodeKind kind);
			GraphQLTypeDefinition(ASTNodeKind kind, std::shared_ptr<GraphQLName> name);

			std::shared_ptr<GraphQLName> Name;
		};
	}
}

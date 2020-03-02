#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLOperationTypeDefinition : public ASTNode {
		public:
			ASTNodeKind Kind = ASTNodeKind::OperationTypeDefinition;

			OperationType Operation;

			GraphQLNamedType Type;
		};
	}
}

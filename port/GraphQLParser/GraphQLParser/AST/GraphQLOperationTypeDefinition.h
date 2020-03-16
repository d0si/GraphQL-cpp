#pragma once

#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLOperationTypeDefinition : public ASTNode {
		public:
			GraphQLOperationTypeDefinition();
			GraphQLOperationTypeDefinition(OperationType operation, GraphQLNamedType type);

			OperationType Operation;

			GraphQLNamedType Type;
		};
	}
}

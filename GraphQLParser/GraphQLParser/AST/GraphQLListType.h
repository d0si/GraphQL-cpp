#pragma once

#include <GraphQLParser/AST/GraphQLType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLListType : public GraphQLType {
		public:
			GraphQLListType(GraphQLType type);

			ASTNodeKind Kind = ASTNodeKind::ListType;

			GraphQLType Type;
		};
	}
}

#pragma once

#include <GraphQLParser/AST/GraphQLType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLNonNullType : public GraphQLType {
		public:
			ASTNodeKind Kind = ASTNodeKind::NonNullType;

			GraphQLType Type;
		};
	}
}

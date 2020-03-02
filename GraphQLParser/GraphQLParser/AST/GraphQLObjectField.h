#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLName.h>
#include <GraphQLParser/AST/GraphQLValue.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLObjectField: public ASTNode {
		public:
			ASTNodeKind Kind = ASTNodeKind::ObjectField;

			GraphQLName Name;

			GraphQLValue Value;
		};
	}
}

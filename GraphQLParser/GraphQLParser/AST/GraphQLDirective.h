#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLArgument.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDirective : public ASTNode {
		public:
			std::vector<GraphQLArgument> Arguments;

			ASTNodeKind Kind = ASTNodeKind::Directive;

			GraphQLName Name;
		};
	}
}

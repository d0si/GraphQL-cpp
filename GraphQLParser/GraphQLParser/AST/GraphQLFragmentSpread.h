#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFragmentSpread : public ASTNode {
		public:
			std::vector<GraphQLDirective> Directives;

			ASTNodeKind Kind = ASTNodeKind::FragmentSpread;

			GraphQLName Name;
		};
	}
}

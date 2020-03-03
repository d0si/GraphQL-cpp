#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFragmentSpread : public ASTNode {
		public:
			GraphQLFragmentSpread();
			GraphQLFragmentSpread(GraphQLName name, std::vector<GraphQLDirective> directives);

			GraphQLName Name;

			std::vector<GraphQLDirective> Directives;
		};
	}
}

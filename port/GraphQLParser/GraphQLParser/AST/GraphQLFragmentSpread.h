#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFragmentSpread : public ASTNode {
		public:
			GraphQLFragmentSpread();
			GraphQLFragmentSpread(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives);

			std::shared_ptr<GraphQLName> Name;

			std::vector<GraphQLDirective> Directives;
		};
	}
}

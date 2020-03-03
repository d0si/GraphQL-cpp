#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLArgument.h>
#include <GraphQLParser/AST/GraphQLName.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLDirective : public ASTNode {
		public:
			GraphQLDirective();
			GraphQLDirective(GraphQLName name);
			GraphQLDirective(GraphQLName name, std::vector<GraphQLArgument> arguments);

			GraphQLName Name;

			std::vector<GraphQLArgument> Arguments;
		};
	}
}

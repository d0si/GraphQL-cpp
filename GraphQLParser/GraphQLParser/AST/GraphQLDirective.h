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
			GraphQLDirective(std::shared_ptr<GraphQLName> name);
			GraphQLDirective(std::shared_ptr<GraphQLName> name, std::vector<GraphQLArgument> arguments);

			std::shared_ptr<GraphQLName> Name;

			std::vector<GraphQLArgument> Arguments;
		};
	}
}

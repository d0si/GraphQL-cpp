#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLScalarTypeDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLScalarTypeDefinition();
			GraphQLScalarTypeDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives);

			std::vector<GraphQLDirective> Directives;
		};
	}
}

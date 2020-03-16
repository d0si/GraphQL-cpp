#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLEnumValueDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLEnumValueDefinition();
			GraphQLEnumValueDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives);

			std::vector<GraphQLDirective> Directives;
		};
	}
}

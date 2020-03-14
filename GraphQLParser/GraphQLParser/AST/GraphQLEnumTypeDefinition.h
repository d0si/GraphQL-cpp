#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLEnumValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLEnumTypeDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLEnumTypeDefinition();
			GraphQLEnumTypeDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives, std::vector<GraphQLEnumValueDefinition> values);

			std::vector<GraphQLDirective> Directives;

			std::vector<GraphQLEnumValueDefinition> Values;
		};
	}
}

#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLValue.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLInputValueDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLInputValueDefinition();
			GraphQLInputValueDefinition(GraphQLName name, GraphQLType type, GraphQLValue default_value, std::vector<GraphQLDirective> directives);

			GraphQLType Type;

			GraphQLValue DefaultValue;

			std::vector<GraphQLDirective> Directives;

		};
	}
}

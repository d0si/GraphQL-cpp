#pragma once

#include <memory>
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
			GraphQLInputValueDefinition(std::shared_ptr<GraphQLName> name, GraphQLType type, std::shared_ptr<GraphQLValue> default_value, std::vector<GraphQLDirective> directives);

			GraphQLType Type;

			std::shared_ptr<GraphQLValue> DefaultValue;

			std::vector<GraphQLDirective> Directives;

		};
	}
}

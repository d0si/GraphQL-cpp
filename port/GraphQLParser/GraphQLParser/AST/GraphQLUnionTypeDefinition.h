#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLUnionTypeDefinition : public GraphQLTypeDefinition {
		public:
			GraphQLUnionTypeDefinition(std::shared_ptr<GraphQLName> name, std::vector<GraphQLDirective> directives, std::vector<GraphQLNamedType> types);

			std::vector<GraphQLDirective> Directives;

			std::vector<GraphQLNamedType> Types;
		};
	}
}

#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLEnumValueDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLEnumTypeDefinition : public GraphQLTypeDefinition {
		public:
			ASTNodeKind Kind = ASTNodeKind::EnumTypeDefinition;
			
			std::vector<GraphQLDirective> Directives;

			std::vector<GraphQLEnumValueDefinition> Values;
		};
	}
}

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
			ASTNodeKind Kind = ASTNodeKind::InputValueDefinition;

			GraphQLValue DefaultValue;

			std::vector<GraphQLDirective> Directives;

			GraphQLType Type;
		};
	}
}

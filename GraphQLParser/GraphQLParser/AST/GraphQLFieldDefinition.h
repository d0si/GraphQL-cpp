#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLInputValueDefinition.h>
#include <GraphQLParser/AST/GraphQLType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLFieldDefinition : public GraphQLTypeDefinition {
		public:
			ASTNodeKind Kind = ASTNodeKind::FieldDefinition;

			std::vector<GraphQLInputValueDefinition> Arguments;

			std::vector<GraphQLDirective> Directives;

			GraphQLType Type;
		};
	}
}

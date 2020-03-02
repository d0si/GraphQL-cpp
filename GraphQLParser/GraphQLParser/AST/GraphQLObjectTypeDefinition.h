#pragma once

#include <vector>
#include <GraphQLParser/AST/GraphQLTypeDefinition.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLFieldDefinition.h>
#include <GraphQLParser/AST/GraphQLNamedType.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLObjectTypeDefinition : public GraphQLTypeDefinition {
		public:
			ASTNodeKind Kind = ASTNodeKind::ObjectTypeDefinition;
			
			std::vector<GraphQLDirective> Directives;

			std::vector<GraphQLFieldDefinition> Fields;

			std::vector<GraphQLNamedType> Interfaces;
		};
	}
}

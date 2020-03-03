#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLOperationTypeDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLSchemaDefinition : public ASTNode {
		public:
			GraphQLSchemaDefinition(std::vector<GraphQLDirective> directives, std::vector<GraphQLOperationTypeDefinition> operation_types);

			std::vector<GraphQLDirective> Directives;

			std::vector<GraphQLOperationTypeDefinition> OperationTypes;
		};
	}
}

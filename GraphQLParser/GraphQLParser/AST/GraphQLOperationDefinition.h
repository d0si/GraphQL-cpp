#pragma once

#include <vector>
#include <GraphQLParser/AST/ASTNode.h>
#include <GraphQLParser/AST/GraphQLDirective.h>
#include <GraphQLParser/AST/GraphQLSelectionSet.h>
#include <GraphQLParser/AST/GraphQLVariableDefinition.h>

namespace GraphQLParser {
	namespace AST {
		class GraphQLOperationDefinition : public ASTNode {
		public:
			GraphQLOperationDefinition();
			GraphQLOperationDefinition(OperationType operation, GraphQLSelectionSet selection_set);
			GraphQLOperationDefinition(
				OperationType operation,
				GraphQLName name,
				std::vector<GraphQLVariableDefinition> variable_definitions,
				std::vector<GraphQLDirective> directives,
				GraphQLSelectionSet selection_set
			);

			OperationType Operation;

			GraphQLName Name;

			std::vector<GraphQLVariableDefinition> VariableDefinitions;
			
			std::vector<GraphQLDirective> Directives;
			
			GraphQLSelectionSet SelectionSet;
		};
	}
}

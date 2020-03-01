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
			std::vector<GraphQLDirective> Directives;

			ASTNodeKind Kind = ASTNodeKind::OperationDefinition;

			GraphQLName Name;

			OperationType Operation;

			GraphQLSelectionSet SelectionSet;

			std::vector<GraphQLVariableDefinition> VariableDefinitions;
		};
	}
}
